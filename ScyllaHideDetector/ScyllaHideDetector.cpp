#include <iostream>
#include "utils/ntdll.h"
#include "utils/common.h"
#include "MemoryMaster/pch.h"
#include "MemoryMaster/SigFinder.h"
#include "ScyllaHideDetector.h"

int main()
{
	// ntdll.dll
	scyllahide_nt_set_information_thread();
	scyllahide_nt_set_information_process();
	scyllahide_nt_query_system_information();
	scyllahide_nt_query_information_process();
	scyllahide_nt_query_object();
	scyllahide_nt_yield_execution();
	scyllahide_nt_create_thread_ex();
	scyllahide_nt_set_debug_filter_state();
	scyllahide_nt_close();
	scyllahide_nt_query_performance_counter();
	scyllahide_nt_get_context_thread();
	scyllahide_nt_set_context_thread();
	// kernel32.dll
	scyllahide_get_tick_count();
	scyllahide_get_tick_count64();
	scyllahide_output_debug_string_a();
	scyllahide_getlocaltime();
	scyllahide_getsystemtime();


#ifdef _WIN64
	if (NtCurrentPeb()->OSBuildNumber >= 14393)
	{
		// win32u.dll
		//TODO: добавить функционал для windows 10
	}
	else
	{
		// user32.dll signatures
		LoadLibraryA("user32.dll");
		//DebugBreak();
		auto finder = MemoryMaster::SigFinder("user32.dll");
		///----------------------------------------------------------------------------------------------------
		// TODO: сделать сигнатуру ScyllaHide и добавить поддержку x86
		// на данный момент это сигнатура отсутствия ScyllaHide
		const auto nt_user_find_window_ex_sig = finder.Find(
			"\x4C\x8B\xD1\xB8\x00\x00\x00\x00\x0F\x05\xC3\xFF\x15\x9F\x85\x0A\x00"
			"\xE9",
			"xxxx????xxxxxxxxxx");

		if (!nt_user_find_window_ex_sig)
		{
			std::cout << "[DETECTED] FindWindowA" << std::endl;
		}
		else
		{
			std::cout << "[OK] FindWindowA" << std::endl;
		}

		///----------------------------------------------------------------------------------------------------
		const auto scyllahide_block_input_sig = finder.Find(
			"\x4C\x8B\xD1\xB8\x00\x00\x00\x00\x0F\x05\xC3\x90\x90\x90\x90\x90\x90"
			"\xFF\x25\x00\x00\x00\x00",
			"xxxx????xxxxxxxxxxxxxxx");

		if (scyllahide_block_input_sig)
		{
			std::cout << "[DETECTED] BlockInput" << std::endl;
		}
		else
		{
			std::cout << "[OK] BlockInput" << std::endl;
		}

		///----------------------------------------------------------------------------------------------------
		const auto scyllahide_nt_user_query_window_sig = finder.Find(
			"\xEB\x01\xCC\x90\xFF\x25\x00\x00\x00\x00\x9C\x1F", "xxxxxxxxxxxx");

		if (scyllahide_nt_user_query_window_sig)
		{
			std::cout << "[DETECTED] NtUserQueryWindow" << std::endl;
		}
		else
		{
			std::cout << "[OK] NtUserQueryWindow" << std::endl;
		}
	}
#endif
	system("pause");
}
