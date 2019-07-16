#pragma once

#include "Structures.h"


namespace MemoryMaster {
	namespace WinUtils {
		void* GetModule(const char* moduleName, PMODULE detailed = nullptr);
		DWORD GetPID(const char* processName);
	}
	
}