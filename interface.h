#pragma once
#include <vector>
#include <cstdint>
#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <psapi.h>
#include <winternl.h>

inline int MOUSE_LEFT_BUTTON_DOWN = 0x0001;  // Left Button changed to down.
inline int MOUSE_LEFT_BUTTON_UP = 0x0002;  // Left Button changed to up.
inline int MOUSE_RIGHT_BUTTON_DOWN = 0x0004;  // Right Button changed to down.
inline int MOUSE_RIGHT_BUTTON_UP = 0x0008;  // Right Button changed to up.
inline int MOUSE_MIDDLE_BUTTON_DOWN = 0x0010;  // Middle Button changed to down.
inline int MOUSE_MIDDLE_BUTTON_UP = 0x0020;  // Middle Button changed to up.


inline uintptr_t virtualaddy;
inline uintptr_t pid;


#define read_write_code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x5AF21, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define cr32_code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1C1B3, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define get_base_code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x24A6D, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define loadedcheck_code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x74A6D, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define hidewindow_code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x9BC1A, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define mouse_code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x62B8E, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef struct _lc {
    uintptr_t* buffer;
} lca, * plc;

typedef struct _ba {
    INT32 process_id;
    ULONGLONG* address;
    uintptr_t* buffer;
    PWCHAR processname;
    PWCHAR modulename;
} ba, * pba;

typedef struct _dtb {
    INT32 process_id;
    bool* operation;
    uintptr_t* cr3_buffer;
} dtb, * dtbl;

typedef struct _RW {
    INT32 process_id;
    ULONGLONG address;
    ULONGLONG buffer;
    ULONGLONG size;
    BOOLEAN write;
} RW, * PRW;

typedef struct _me {
    long mouse_x;
    long mouse_y;
    unsigned short mouse_flags;
} me, * mevent;

typedef struct _hw {
    uint32_t address;
    uint64_t handle;
    bool* success;
} hw, * phw;

namespace drv {
    inline const wchar_t* target_process = L"RustClient.exe";
    inline HANDLE driver_handle;
    inline INT32 process_id;
    inline uintptr_t process_base;
    inline uintptr_t process_cr3;

    inline bool initialize() {
        driver_handle = CreateFileW(L"\\\\.\\WinIo", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

        if (driver_handle == INVALID_HANDLE_VALUE) {
            printf("Driver not found. Error: %lu\n", GetLastError());
            return false;
        }

        printf("Driver handle found at: %u\n", driver_handle);
        return true;
    }

    inline INT32 set_pid(const std::uint32_t pid) { // attach to program basically
        process_id = pid;
        return process_id;
    }

    inline uintptr_t set_cr3() {
        uintptr_t image_address = { NULL };
        bool operation = false;
        _dtb arguments = { NULL };

        arguments.process_id = process_id;
        arguments.cr3_buffer = &image_address;
        arguments.operation = &operation;

        if (!DeviceIoControl(driver_handle, cr32_code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL)) {
            printf("Failed to find driver. Error: %lu\n", GetLastError());
        }

        return image_address;
    }

    inline uintptr_t find_process_base() {
        uintptr_t image_address = { NULL };
        _ba arguments = { NULL };

        arguments.process_id = process_id;
        arguments.address = (ULONGLONG*)&image_address;

        if (!DeviceIoControl(driver_handle, get_base_code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL)) {
            printf("Failed to find process base. Error: %lu\n", GetLastError());
        }
        return image_address;
    }

    inline INT32 find_process(LPCTSTR process_name) {
        PROCESSENTRY32 pt;
        HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        pt.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hsnap, &pt)) {
            do {
                if (!lstrcmpi(pt.szExeFile, process_name)) {
                    CloseHandle(hsnap);
                    process_id = pt.th32ProcessID;
                    return pt.th32ProcessID;
                }
            } while (Process32Next(hsnap, &pt));
        }
        CloseHandle(hsnap);

        return { NULL };
    }

    inline bool is_driver_loaded() {
        uintptr_t image_address = { NULL };
        _lc arguments = { NULL };
        bool loaded = false;

        arguments.buffer = (ULONGLONG*)&image_address;

        if (!DeviceIoControl(driver_handle, loadedcheck_code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL)) {
            printf("Failed to find driver. Error: %lu\n", GetLastError());
        }

        if (image_address == 0x5894)
            loaded = true;

        return loaded;
    }

    inline bool read_physical(PVOID address, PVOID buffer, DWORD size) {
        _RW arguments = { 0 };

        arguments.address = (ULONGLONG)address;
        arguments.buffer = (ULONGLONG)buffer;
        arguments.size = size;
        arguments.process_id = drv::process_id;
        arguments.write = FALSE;

        // Call DeviceIoControl and check if it succeeded
        if (DeviceIoControl(drv::driver_handle, read_write_code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL)) {
            return true; // Success
        }
        else {
            return false; // Failure
        }
    }


    inline void write_physical(PVOID address, PVOID buffer, DWORD size) {
        _RW arguments = { 0 };

        arguments.address = (ULONGLONG)address;
        arguments.buffer = (ULONGLONG)buffer;
        arguments.size = size;
        arguments.process_id = drv::process_id;
        arguments.write = TRUE;

        DeviceIoControl(drv::driver_handle, read_write_code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
    }

    inline bool is_valid(const uint64_t address)
    {
        if (address == 0 || address == 0xCCCCCCCCCCCCCCCC || address == 0xFFFFFFFFFFFFFFFF)
            return false;

        if (address <= 0x400000 || address > 0x7FFFFFFFFFFFFFFF)
            return false;

        return true;
    }

    inline bool hidewindow(uint32_t value, HWND windowhandle) {
        _hw arguments = { NULL };
        bool loaded = false;

        arguments.address = value;
        arguments.handle = reinterpret_cast<uint64_t>(windowhandle);
        arguments.success = (bool*)&loaded;

        if (!DeviceIoControl(driver_handle, hidewindow_code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL)) {
            printf("Failed to hide window. Error: %lu\n", GetLastError());
        }

        return loaded;
    }

    inline  void mouse_input(long xpos, long ypos, unsigned short mouseflags) {
        _me arguments = { 0 };
        arguments.mouse_flags = mouseflags;
        arguments.mouse_x = xpos;
        arguments.mouse_y = ypos;

        if (!DeviceIoControl(driver_handle, mouse_code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL)) {
            //  printf("Failed to send mouse input. Error: %lu\n", GetLastError());
        }
    }

    inline void mouseclick(int ms, int button_down, int button_up) {
        drv::mouse_input(0, 0, button_down);
        Sleep(ms);
        drv::mouse_input(0, 0, button_up);
    }
}
inline bool is_valid(const uint64_t adress)
{
	if (adress <= 0x400000 || adress == 0xCCCCCCCCCCCCCCCC || reinterpret_cast<void*>(adress) == nullptr || adress >
		0x7FFFFFFFFFFFFFFF) {
		return false;
	}
	return true;
}

template <typename T>
inline T Read(uint64_t address) {
	T buffer{ };
	if (!address || !is_valid(address))return buffer;

    drv::read_physical(reinterpret_cast<PVOID>(address), &buffer, sizeof(T));
	return buffer;
}

template <typename T>
inline T Write(uint64_t address, T buffer) {
	if (!address || !is_valid(address))return buffer;
    drv::write_physical(reinterpret_cast<PVOID>(address), &buffer, sizeof(T));
	return buffer;
}


inline std::string ReadString(uint64_t Address)
{
	std::unique_ptr<char[]> buffer(new char[64]);
	drv::read_physical(reinterpret_cast<PVOID>(Address), buffer.get(), 64);
	return buffer.get();
}
inline std::string read_wstr(uintptr_t address)
{
	if (!Read<uintptr_t>(address))return"";
	wchar_t buffer[1024 * sizeof(wchar_t)];
    drv::read_physical(reinterpret_cast<PVOID>(address), &buffer, 1024 * sizeof(wchar_t));

	std::wstring new_buffer = std::wstring(buffer);

	return std::string(new_buffer.begin(), new_buffer.end());
}

template <typename T>
inline T Read_chain(std::uint64_t address, std::vector<std::uint64_t> chain)
{
	uint64_t cur_read = address;

	for (size_t r = 0; r < chain.size() - 1; ++r)
		cur_read = Read<std::uint64_t>(cur_read + chain[r]);

	return Read<T>(cur_read + chain[chain.size() - 1]);
}

inline int PID(std::string name)
{
	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 entry{ };
	entry.dwSize = sizeof(PROCESSENTRY32);

	Process32First(snapshot, &entry);
	do
	{
		if (!name.compare(entry.szExeFile))
		{
			return entry.th32ProcessID;
		}

	} while (Process32Next(snapshot, &entry));
}
inline void cachCr3()
{
	
}