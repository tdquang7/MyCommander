#include "DriveInfo.h"
#include <windows.h>
using namespace System::IO;

DriveInfo::DriveInfo(std::wstring root, DriveType type)
    : _root(std::move(root)), _type(type)
{
}

std::vector<DriveInfo> DriveInfo::GetDrives() {
    std::vector<DriveInfo> drives;

    DWORD mask = GetLogicalDrives();

    for (int i = 0; i < 26; ++i) {
        if (mask & (1 << i)) {
            wchar_t root[] = L"A:\\";
            root[0] = L'A' + i;

            UINT type = GetDriveTypeW(root);

            DriveType dt = DriveType::Unknown;

            switch (type) {
                case DRIVE_FIXED:     dt = DriveType::Fixed;     break;
                case DRIVE_REMOVABLE: dt = DriveType::Removable; break;
                case DRIVE_CDROM:     dt = DriveType::CDROM;     break;
                case DRIVE_REMOTE:    dt = DriveType::Network;   break;
                case DRIVE_RAMDISK:   dt = DriveType::RAMDisk;   break;
            }

            drives.emplace_back(root, dt);
        }
    }

    return drives;
}

std::wstring DriveInfo::Name() const {
    return _root;
}

DriveType DriveInfo::Type() const {
    return _type;
}

std::wstring DriveInfo::TypeString() const {
    switch (_type) {
        case DriveType::Removable: return L"Removable";
        case DriveType::Fixed:     return L"Fixed";
        case DriveType::Network:   return L"Network";
        case DriveType::CDROM:     return L"CDROM";
        case DriveType::RAMDisk:   return L"RAMDisk";
        default:                   return L"Unknown";
    }
}

std::wstring DriveInfo::VolumeLabel() const
{
    _loadVolumeInfo();
    return _volumeLabel;
}

std::wstring DriveInfo::FileSystem() const
{
    _loadVolumeInfo();
    return _fileSystem;
}

uint64_t DriveInfo::TotalSpace() const {
    ULARGE_INTEGER total{};
    if (GetDiskFreeSpaceExW(_root.c_str(), nullptr, &total, nullptr))
        return total.QuadPart;

    return 0;
}

uint64_t DriveInfo::FreeSpace() const {
    ULARGE_INTEGER free{};
    if (GetDiskFreeSpaceExW(_root.c_str(), &free, nullptr, nullptr))
        return free.QuadPart;

    return 0;
}

double DriveInfo::TotalSpaceGB() const {
    return TotalSpace() / (1024.0 * 1024 * 1024);
}

void DriveInfo::_loadVolumeInfo() const
{
    if (_volumeLoaded)
        return;

    wchar_t volumeName[MAX_PATH] = {};
    wchar_t fileSystemName[MAX_PATH] = {};

    DWORD serialNumber = 0;
    DWORD maxComponentLen = 0;
    DWORD fileSystemFlags = 0;

    if (GetVolumeInformationW(
        _root.c_str(),
        volumeName,
        MAX_PATH,
        &serialNumber,
        &maxComponentLen,
        &fileSystemFlags,
        fileSystemName,
        MAX_PATH))
    {
        _volumeLabel = volumeName;
        _fileSystem = fileSystemName;
    }

    _volumeLoaded = true;
}