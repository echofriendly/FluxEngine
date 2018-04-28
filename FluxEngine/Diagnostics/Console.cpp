#include "FluxEngine.h"
#include <time.h>
#include <iomanip>
#include "FileSystem\File\PhysicalFile.h"
#include "Async\Thread.h"
#include "Core\Config.h"

using namespace std;

static Console* consoleInstance = nullptr;
Console::Console()
{
	AUTOPROFILE(Console_Initialize);
	consoleInstance = this;
	m_ConvertBuffer = new char[m_ConvertBufferSize];

	if (Config::GetBool("CleanupLogs", "Console", true))
	{
		CleanupLogs(TimeSpan(Config::GetInt("LogRetention", "Console", 1) * Time::TicksPerDay));
	}

	TimeStamp time;
	DateTime::Now().Split(time);

	std::string filePath = Printf("%s\\%02d-%02d-%02d-%02d-%02d-%02d.log",
		Paths::LogsDir().c_str(),
		time.Year,
		time.Month,
		time.Day,
		time.Hour,
		time.Minute,
		time.Second);

	m_pFileLog = new PhysicalFile(filePath);

	if (!m_pFileLog->OpenWrite())
	{
		FLUX_LOG(Error, "Failed to open console log");
	}

	std::stringstream stream;
	stream << "Date: " << time.Day << "-" << time.Month << "-" << time.Year << std::endl;
	stream << "Time: " << time.Hour << ":" << time.Minute << ":" << time.Second << std::endl << std::endl;

	stream << "Configuration: " << BuildConfiguration::ToString(BuildConfiguration::Configuration) << std::endl;
	stream << "Platform: " << BuildPlatform::ToString(BuildPlatform::Platform) << std::endl;
	Misc::CpuId cpuId;
	Misc::GetCpuId(&cpuId);
	stream << cpuId.Brand << std::endl << std::endl;

	std::string output = stream.str();
	m_pFileLog->Write(output.c_str(), output.size());

#ifdef _DEBUG
		InitializeConsoleWindow();
#endif
}

Console::~Console()
{
	delete m_pFileLog;
	delete[] m_ConvertBuffer;
}

void Console::FlushThreadedMessages()
{
	checkf(Thread::IsMainThread(), "Console::FlushThreadedMessages() must run on the main thread!");
	if (m_MessageQueue.size() == 0)
		return;

	ScopeLock lock(m_QueueMutex);
	while (m_MessageQueue.size() > 0)
	{
		const QueuedMessage& message = m_MessageQueue.front();
		Log(message.Message, message.Type);
		m_MessageQueue.pop();
	}
}

bool Console::LogFmodResult(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		Log(Printf("FMOD Error (%d) %s", result, FMOD_ErrorString(result)), LogType::Error);
		return true;
	}
	return false;
}

bool Console::LogHRESULT(const std::string &source, HRESULT hr)
{
	if (FAILED(hr))
	{
		if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
			hr = HRESULT_CODE(hr);

		std::stringstream ss;
		if (source.size() != 0)
		{
			ss << "Source: ";
			ss << source;
			ss << "\n";
		}
		ss << "Message: ";

		TCHAR* errorMsg;
		if (FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&errorMsg, 0, nullptr) != 0)
		{
			ss << errorMsg;
		}
		else
		{
			ss << "Could not find a description for error: '";
			ss << hr;
			ss << "'.";
		}

		Log(ss.str(), LogType::Error);
		return true;
	}

	return false;
}

bool Console::LogHRESULT(char* source, HRESULT hr)
{
	return LogHRESULT(std::string(source), hr);
}

void Console::Log(const std::string &message, LogType type)
{
	if (!Thread::IsMainThread())
	{
		ScopeLock lock(consoleInstance->m_QueueMutex);
		consoleInstance->m_MessageQueue.push(QueuedMessage(message, type));
	}
	else
	{
		stringstream stream;
		DateTime now = DateTime::Now();
		stream << "[" << now.GetHours() << ":" << now.GetMinutes() << ":" << now.GetSeconds() << "]";
		switch (type)
		{
		case LogType::Info:
			stream << "[INFO] ";
			break;
		case LogType::Warning:
			if (consoleInstance->m_ConsoleHandle)
				SetConsoleTextAttribute(consoleInstance->m_ConsoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			stream << "[WARNING] ";
			break;
		case LogType::Error:
			if (consoleInstance->m_ConsoleHandle)
				SetConsoleTextAttribute(consoleInstance->m_ConsoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
			stream << "[ERROR] ";
			break;
		default:
			break;
		}

		stream << message;
		std::string output = stream.str();

		std::cout << output << std::endl;
		if (consoleInstance->m_ConsoleHandle)
			SetConsoleTextAttribute(consoleInstance->m_ConsoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		consoleInstance->m_pFileLog->WriteLine(output.c_str());

		if (type == LogType::Error)
		{
			MessageBox(nullptr, message.c_str(), "Fatal Error", MB_ICONINFORMATION);
			//PostQuitMessage(-1);
			//__debugbreak();
			abort();
		}
	}
}

void Console::LogWarning(const std::string& message)
{
	Log(message, LogType::Warning);
}

void Console::LogError(const std::string& message)
{
	Log(message, LogType::Error);
}

void Console::LogFormat(LogType type, const char* format, ...)
{
	va_list ap;

	va_start(ap, format);
	_vsnprintf_s(&consoleInstance->m_ConvertBuffer[0], consoleInstance->m_ConvertBufferSize, consoleInstance->m_ConvertBufferSize, format, ap);
	va_end(ap);
	Log(&consoleInstance->m_ConvertBuffer[0], type);
}

void Console::LogFormat(LogType type, const std::string& format, ...)
{
	va_list ap;

	const char* f = format.c_str();
	va_start(ap, f);
	_vsnprintf_s(&consoleInstance->m_ConvertBuffer[0], consoleInstance->m_ConvertBufferSize, consoleInstance->m_ConvertBufferSize, f, ap);
	va_end(ap);
	Log(&consoleInstance->m_ConvertBuffer[0], type);
}

bool Console::CleanupLogs(const TimeSpan& age)
{
	struct LogCleaner : public FileVisitor
	{
		LogCleaner(const TimeSpan& maxAge) :
			MaxAge(maxAge), Now(DateTime::Now())
		{
		}
		TimeSpan MaxAge;
		DateTime Now;

		virtual bool Visit(const std::string& fileName, const bool isDirectory) override
		{
			const std::string path = Paths::LogsDir() + fileName;
			if (isDirectory == false && Paths::GetFileExtenstion(fileName) == "log")
			{
				const TimeSpan age = Now - FileSystem::GetCreationTime(path);
				if (age > MaxAge)
				{
					FileSystem::Delete(path);
				}
			}
			return true;
		}

		virtual bool IsRecursive() const override
		{
			return false;
		}
	};
	LogCleaner cleaner(age);
	return FileSystem::IterateDirectory(Paths::LogsDir(), cleaner);
}

void Console::InitializeConsoleWindow()
{
	if (AllocConsole())
	{
		// Redirect the CRT standard input, output, and error handles to the console
		FILE* pCout;
		freopen_s(&pCout, "CONIN$", "r", stdin);
		freopen_s(&pCout, "CONOUT$", "w", stdout);
		freopen_s(&pCout, "CONOUT$", "w", stderr);

		//Clear the error state for each of the C++ standard stream objects. We need to do this, as
		//attempts to access the standard streams before they refer to a valid target will cause the
		//iostream objects to enter an error state. In versions of Visual Studio after 2005, this seems
		//to always occur during startup regardless of whether anything has been read from or written to
		//the console or not.
		std::wcout.clear();
		std::cout.clear();
		std::wcerr.clear();
		std::cerr.clear();
		std::wcin.clear();
		std::cin.clear();

		//Set ConsoleHandle
		m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		//Disable Close-Button
		HWND hwnd = GetConsoleWindow();
		if (hwnd != nullptr)
		{
			HMENU hMenu = GetSystemMenu(hwnd, FALSE);
			if (hMenu != nullptr)
				DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
		}
	}
}