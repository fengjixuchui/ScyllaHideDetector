#pragma once

#include "Structures.h"


namespace MemoryMaster {
	namespace WinUtils {
		void* GetModule(const char* moduleName, PMODULE detailed = nullptr);
		void* GetFunctionPEB(LPWSTR dllName, const char* functionName);
		void* GetFunctionFromExports(const char* function, PVOID base);
		void* GetModulePEB(const LPWSTR moduleName);
		DWORD GetPID(const char* processName);
	}
	
}