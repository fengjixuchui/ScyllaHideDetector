#include "pch.h"
#include "WinUtils.h"
#include "External.h"

InjectStatus MemoryMaster::External::Injector::InjectDLL(const char* dll, DWORD pid) {
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (process == INVALID_HANDLE_VALUE) {
		return InjectStatus::ERR_OPEN_PROCESS;
	}

	char fullFilename[MAX_PATH];
	const char* filename = dll;
	GetFullPathNameA(filename, MAX_PATH, fullFilename, nullptr);

	SIZE_T _fixed = strlen(fullFilename) + 1;

	LPVOID dllNameAllocated = VirtualAllocEx(
		process,
		NULL,
		_fixed,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_READWRITE
	);

	if (!dllNameAllocated) {
		return InjectStatus::ERR_WRITE_DLL_NAME;
	}

	SIZE_T written;
	BOOL writeSuccess = WriteProcessMemory(process, dllNameAllocated, fullFilename, _fixed, &written);

	if (!writeSuccess) {
		return InjectStatus::ERR_WRITE_DLL_NAME;
	}

	HMODULE kernel32 = GetModuleHandleA("kernel32.dll");

	if (!kernel32) {
		return InjectStatus::ERR_WRITE_DLL_NAME;
	}

	LPVOID loadLibrary = GetProcAddress(kernel32, "LoadLibraryA");

	if (loadLibrary == 0) {
		return InjectStatus::ERR_GET_LOADLIBRARY;
	}

	HANDLE _thread = CreateRemoteThread(
		process,
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)loadLibrary,
		dllNameAllocated,
		0,
		NULL);

	CloseHandle(process);

	return InjectStatus::SUCCESS;
}

InjectStatus MemoryMaster::External::Injector::InjectDLL(const char* dll, const char* processName) {
	DWORD pid = MemoryMaster::WinUtils::GetPID(processName);

	return MemoryMaster::External::Injector::InjectDLL(dll, pid);
}