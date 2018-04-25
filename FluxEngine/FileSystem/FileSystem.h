#pragma once
class IMountPoint;
class PhysicalMountPoint;
class PakMountPoint;
class File;
class PhysicalFile;
class PakFile;

enum class ArchiveType
{
	Physical,
	Pak,
};

using MountPointPair = std::pair<std::string, std::unique_ptr<IMountPoint>>;

struct FileAttributes
{
	DateTime CreationTime;
	DateTime AccessTime;
	DateTime ModifiedTime;
	long long Size = -1;
	bool IsReadOnly = false;
	bool IsDirectory = false;
};

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	static bool Mount(const std::string& path, const ArchiveType type = ArchiveType::Physical);
	static bool Mount(const std::string& physicalPath, const std::string& virtualPath, const ArchiveType type = ArchiveType::Physical);

	static void AddPakLocation(const std::string& path, const std::string& virtualPath);

	static std::unique_ptr<File> GetFile(const std::string& fileName);
	static DateTime GetLastModifiedTime(const std::string& fileName);

private:
	static bool GetFileAttributes(const std::string filePath, FileAttributes& attributes);

	static void GetFilesInDirectory(const std::string& directory, std::vector<std::string>& files, const bool recursive);

	static std::vector<std::string> GetPakFilesInDirectory(const std::string& directory);

	static std::string FixPath(const std::string& path);
	static std::unique_ptr<IMountPoint> CreateMountPoint(const std::string& physicalPath, const ArchiveType type);
	static std::vector<MountPointPair> m_MountPoints;

	static std::vector<std::string> m_PakLocations;
};