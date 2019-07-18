#include "pch.h"
#include "WinUtils.h"

DWORD MemoryMaster::WinUtils::GetPID(const char* processName) {
	PROCESSENTRY32 currentProcess;
	currentProcess.dwSize = sizeof(PROCESSENTRY32);

	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(handle, &currentProcess)) {
		while (Process32Next(handle, &currentProcess)) {

			wchar_t tmp[255];

			mbstowcs(tmp, processName, 255);

			if (lstrcmpW(currentProcess.szExeFile, tmp) == 0) {
				CloseHandle(handle);
				return currentProcess.th32ProcessID;
			}
		}
	}

	CloseHandle(handle);

	return 0;
}

void* MemoryMaster::WinUtils::GetModule(const char* moduleName, PMODULE detailed) {
	DWORD sizeRequired;
	HMODULE* modules;

	HANDLE process = GetCurrentProcess();

	BOOL result = EnumProcessModules(process, 0, 0, &sizeRequired);

	if (!result) {
		CloseHandle(process);

		return nullptr;
	}

	modules = (HMODULE*)malloc(sizeRequired);

	unsigned int moduleCount;


	moduleCount = sizeRequired / sizeof(HMODULE);

	if (EnumProcessModules(process, modules, sizeRequired, &sizeRequired))
	{
		for (size_t i = 0; i < moduleCount; i++) {
			HMODULE module = modules[i];

			char _baseName[512];

			GetModuleBaseNameA(process, module, _baseName, 512);

			if (strcmp(_baseName, moduleName) == 0) {
				MODULEINFO info = { 0 };

				BOOL good = GetModuleInformation(process, module, &info, sizeof(MODULEINFO));

				if (!good) {
					CloseHandle(process);
					free(modules);

					return nullptr;
				}

				if (detailed != nullptr) {
					detailed->base = info.lpBaseOfDll;
					detailed->size = info.SizeOfImage;
				}

				

				return info.lpBaseOfDll;
			}
		}
	}

	free(modules);

	return nullptr;
}

void* MemoryMaster::WinUtils::GetModulePEB(const LPWSTR moduleName) {

#ifdef _WIN64
	UINT peb = (UINT)__readgsqword(0x60);
	UINT offset = 0x18;
#else
	UINT peb = (UINT)__readfsdword(0x30);
	UINT offset = 0x0C;
#endif

	UINT moduleListAddr = *(UINT*)(peb + offset);
	PVOID start = *(PVOID*)(moduleListAddr + offset);

	LDR_ENTRY * mod = (LDR_ENTRY*)start;
	mod = (LDR_ENTRY*)mod->Orders[0].Flink;

	while ((UINT)start != (UINT)mod) {

		if (mod->Base != NULL)
		{
			if (!lstrcmpiW((LPCWSTR)mod->DllName.Buffer, moduleName))
			{
				return mod->Base;
			}
		}

		mod = (LDR_ENTRY*)mod->Orders[0].Flink;
	}

	return 0;
}

void* MemoryMaster::WinUtils::GetFunctionFromExports(const char* functionName, PVOID base) {
	IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)base;

#ifdef _WIN64
	IMAGE_NT_HEADERS64* ntHeaders = (IMAGE_NT_HEADERS64*)((UINT)base + dosHeader->e_lfanew);
#else
	IMAGE_NT_HEADERS* ntHeaders = (IMAGE_NT_HEADERS*)((UINT)base + dosHeader->e_lfanew);
#endif
	

	IMAGE_EXPORT_DIRECTORY * exportTable =
		(IMAGE_EXPORT_DIRECTORY*)((UINT)base + ntHeaders->OptionalHeader.DataDirectory[0].VirtualAddress);

	DWORD * functions = (DWORD*)((UINT)base + exportTable->AddressOfFunctions);
	WORD * ords = (WORD*)((UINT)base + exportTable->AddressOfNameOrdinals);
	DWORD * names = (DWORD*)((UINT)base + exportTable->AddressOfNames);

	for (int i = 0; i < exportTable->NumberOfNames; i++) {
		char* data = (char*)((UINT)base + (UINT)names[i]);

		if (lstrcmpA(functionName, data) == 0) {
			return (void*)((UINT)base + (UINT)functions[ords[i]]);
		}
	}

	return nullptr;
}

void* MemoryMaster::WinUtils::GetFunctionPEB(LPWSTR dllName, const char* functionName) {
	void* moduleBase = MemoryMaster::WinUtils::GetModulePEB(dllName);

	if (!moduleBase) {
		return nullptr;
	}

	return MemoryMaster::WinUtils::GetFunctionFromExports(functionName, moduleBase);
}