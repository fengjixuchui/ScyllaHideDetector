#include <iostream>
#include "utils/ntdll.h"
#include "utils/common.h"
#include "MemoryMaster/pch.h"
#include "MemoryMaster/SigFinder.h"
#include "ScyllaHideDetector.h"

int main()
{
	// ntdll.dll
    Scyllahide_NtSetInformationThread();
    Scyllahide_NtSetInformationProcess();
    Scyllahide_NtQuerySystemInformation();
    Scyllahide_NtQueryInformationProcess();
    Scyllahide_NtQueryObject();
    Scyllahide_NtYieldExecution();
    Scyllahide_NtCreateThreadEx();
    Scyllahide_NtSetDebugFilterState();
    Scyllahide_NtClose();
    Scyllahide_NtQueryPerformanceCounter();
    Scyllahide_NtGetContextThread();
	// kernel32.dll
    Scyllahide_GetTickCount();
    Scyllahide_GetTickCount64();
    Scyllahide_OutputDebugStringA();

#ifdef _WIN64
    if (NtCurrentPeb()->OSBuildNumber >= 14393) { // win32u.dll
		//TODO: добавить функционал для windows 10
    }
    else { // user32.dll signatures
        LoadLibraryA("user32.dll");
        //DebugBreak();
        MemoryMaster::SigFinder finder = MemoryMaster::SigFinder("user32.dll");
        ///----------------------------------------------------------------------------------------------------
        // TODO: сделать сигнатуру ScyllaHide и добавить поддержку x86
        // на данный момент это сигнатура отсутствия ScyllaHide
        void* NtUserFindWindowEx_sig = finder.Find(
            "\x4C\x8B\xD1\xB8\x00\x00\x00\x00\x0F\x05\xC3\xFF\x15\x9F\x85\x0A\x00"
            "\xE9",
            "xxxx????xxxxxxxxxx");

        if (!NtUserFindWindowEx_sig) {
            std::cout << "[DETECTED] FindWindowA" << std::endl;
        }
        else {
            std::cout << "[OK] FindWindowA" << std::endl;
        }

        ///----------------------------------------------------------------------------------------------------
        void* Scyllahide_BlockInput_sig = finder.Find(
            "\x4C\x8B\xD1\xB8\x00\x00\x00\x00\x0F\x05\xC3\x90\x90\x90\x90\x90\x90"
            "\xFF\x25\x00\x00\x00\x00",
            "xxxx????xxxxxxxxxxxxxxx");

        if (Scyllahide_BlockInput_sig) {
            std::cout << "[DETECTED] BlockInput" << std::endl;
        }
        else {
            std::cout << "[OK] BlockInput" << std::endl;
        }

        ///----------------------------------------------------------------------------------------------------
        void* Scyllahide_NtUserQueryWindow_sig = finder.Find(
            "\xEB\x01\xCC\x90\xFF\x25\x00\x00\x00\x00\x9C\x1F", "xxxxxxxxxxxx");

        if (Scyllahide_NtUserQueryWindow_sig) {
            std::cout << "[DETECTED] NtUserQueryWindow" << std::endl;
        }
        else {
            std::cout << "[OK] NtUserQueryWindow" << std::endl;
        }
        ///----------------------------------------------------------------------------------------------------

        LoadLibraryA("ntdll.dll");
        MemoryMaster::SigFinder finder_ntdll = MemoryMaster::SigFinder("ntdll.dll");
        ///----------------------------------------------------------------------------------------------------
        void* Scyllahide_NtSetContextThread_sig = finder_ntdll.Find(
            "\x4C\x8B\xD1\xB8\x00\x00\x00\x00\x0F\x05\xC3\x0F\x1F\x44\x00\x00\x90"
            "\xFF\x25\x00\x00\x00\x00\x7C\x18",
            "xxxx????xxxxxxxxxxxxxxxxx");

        if (Scyllahide_NtSetContextThread_sig) {
            std::cout << "[DETECTED] NtSetContextThread" << std::endl;
        }
        else {
            std::cout << "[OK] NtSetContextThread" << std::endl;
        }
    }
#endif
    system("pause");
}
