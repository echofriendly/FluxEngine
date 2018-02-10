#include "FluxEngine.h"
#include "Http.h"

#include <winsock2.h>
#include <ws2tcpip.h>
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

std::string Http::HttpGet(const std::string& host, const std::string& path)
{
	WSADATA wsaData;

	// Initialize Winsock
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
		throw SocketError("WSAStartUp", result);

	// Resolve the server address and port
	addrinfo * pAddrInfo;
	result = getaddrinfo(host.c_str(), "80", nullptr, &pAddrInfo);
	if (result != 0)
		throw SocketError("addrinfo", result);

	//Create the socket
	SOCKET sock = socket(pAddrInfo->ai_family, pAddrInfo->ai_socktype, pAddrInfo->ai_protocol);

	if (sock == INVALID_SOCKET)
		throw SocketError("Socket", WSAGetLastError());

	// Connect to server.
	result = connect(sock, pAddrInfo->ai_addr, (int)pAddrInfo->ai_addrlen);
	if (result != 0)
		throw SocketError("Connect", WSAGetLastError());

	const std::string request = "GET " + path + " HTTP/1.1\nHost: " + host + "\n\n";

	// Send an initial buffer
	result = send(sock, request.c_str(), (int)request.size(), 0);
	if (result == SOCKET_ERROR)
		throw SocketError("Send", WSAGetLastError());

	// shutdown the connection since no more data will be sent
	result = shutdown(sock, SD_SEND);
	if (result == SOCKET_ERROR)
		throw SocketError("Close send connection", WSAGetLastError());

	// Receive until the peer closes the connection
	std::string response;

	char buffer[RECV_BUFFER_SIZE];
	int bytesRecv = 0;

	for (;;)
	{
		result = recv(sock, buffer, sizeof(buffer), 0);
		if (result == SOCKET_ERROR)
			throw SocketError("Recv", WSAGetLastError());
		if (result == 0)
			break;
		response += std::string(buffer, result);
		std::stringstream stream;
		stream << "HttpGet() > Bytes received: " << bytesRecv;
		FLUX_LOG(Info, stream.str());
		bytesRecv += result;
	}
	std::stringstream stream;
	stream << "HttpGet() > Bytes received: " << bytesRecv;
	FLUX_LOG(Info, stream.str());

	// cleanup
	result = closesocket(sock);
	if (result == SOCKET_ERROR)
		throw SocketError("Closesocket", WSAGetLastError());

	result = WSACleanup();
	if (result == SOCKET_ERROR)
		throw SocketError("WSACleanup", WSAGetLastError());

	freeaddrinfo(pAddrInfo);

	FLUX_LOG(Info, "HttpGet() > Cleanup Successful ");

	return response;
}

std::string SocketError::ErrorMessage(const std::string & context, const int errorCode) const
{
	char buf[1024];
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, errorCode, 0, buf, sizeof(buf), nullptr);
	char * newLine = strchr(buf, '\r');
	if (newLine) *newLine = '\0';
	std::stringstream stream;
	stream << "Socket error in " << context << " (" << errorCode << "): " << buf;
	return stream.str();
}