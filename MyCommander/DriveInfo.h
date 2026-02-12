#pragma once
#include <vector>
#include <string>

namespace System::IO {
	enum class DriveType {
		Fixed,
		Removable,
		CDROM,
		Network,
		RAMDisk,
		Unknown,
	};

	class DriveInfo {
	private:
		std::wstring _root;
		DriveType    _type;
	public:
		std::wstring Name() const;
		DriveType Type() const;
		std::wstring TypeString() const;
		std::wstring VolumeLabel() const;
		std::wstring FileSystem() const;
	public:
		DriveInfo() = default;
		~DriveInfo() = default;
		DriveInfo(std::wstring root, DriveType type);
	public:
		uint64_t TotalSpace() const;
		uint64_t FreeSpace() const;
		double   TotalSpaceGB() const;
	private:
		mutable bool _volumeLoaded{ false };
		mutable std::wstring _volumeLabel;
		mutable std::wstring _fileSystem;
		void _loadVolumeInfo() const;
	public:
		static std::vector<DriveInfo> GetDrives();
	};
}