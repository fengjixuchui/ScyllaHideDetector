#include "pch.h"
#include "WinUtils.h"

DWORD MemoryMaster::WinUtils::GetPID(const char* processName)
{
	PROCESSENTRY32 currentProcess;
	currentProcess.dwSize = sizeof(PROCESSENTRY32);

	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(handle, &currentProcess))
	{
		while (Process32Next(handle, &currentProcess))
		{
			wchar_t tmp[255];

			mbstowcs(tmp, processName, 255);

			if (lstrcmpW(currentProcess.szExeFile, tmp) == 0)
			{
				CloseHandle(handle);
				return currentProcess.th32ProcessID;
			}
		}
	}

	CloseHandle(handle);

	return 0;
}

void* MemoryMaster::WinUtils::GetModule(const char* moduleName, PMODULE detailed)
{
	DWORD sizeRequired;
	HMODULE* modules;

	HANDLE process = GetCurrentProcess();

	BOOL result = EnumProcessModules(process, 0, 0, &sizeRequired);

	if (!result)
	{
		CloseHandle(process);

		return nullptr;
	}

	modules = (HMODULE*)malloc(sizeRequired);

	unsigned int moduleCount;


	moduleCount = sizeRequired / sizeof(HMODULE);

	if (EnumProcessModules(process, modules, sizeRequired, &sizeRequired))
	{
		for (size_t i = 0; i < moduleCount; i++)
		{
			HMODULE module = modules[i];

			char _baseName[512];

			GetModuleBaseNameA(process, module, _baseName, 512);

			if (strcmp(_baseName, moduleName) == 0)
			{
				MODULEINFO info = {0};

				BOOL good = GetModuleInformation(process, module, &info, sizeof(MODULEINFO));

				if (!good)
				{
					CloseHandle(process);
					free(modules);

					return nullptr;
				}

				if (detailed != nullptr)
				{
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
