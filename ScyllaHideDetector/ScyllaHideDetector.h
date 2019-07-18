#pragma once
#include "utils/common.h"

inline void scyllahide_nt_set_information_thread()
{
	const auto func = MemoryMaster::WinUtils::GetFunctionPEB((LPWSTR)L"ntdll.dll", "NtSetInformationThread");

	const auto func_bytes = reinterpret_cast<BYTE*>(func);

	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] NtSetInformationThread" << std::endl;
	}
	else
	{
		std::cout << "[OK] NtSetInformationThread" << std::endl;
	}
}

inline void scyllahide_nt_set_information_process()
{
	const auto func = MemoryMaster::WinUtils::GetFunctionPEB((LPWSTR)L"ntdll.dll", "NtSetInformationProcess");

	auto* func_bytes = reinterpret_cast<BYTE*>(func);

	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] NtSetInformationProcess" << std::endl;
	}
	else
	{
		std::cout << "[OK] NtSetInformationProcess" << std::endl;
	}
}

inline void scyllahide_nt_query_system_information()
{
	const auto func = MemoryMaster::WinUtils::GetFunctionPEB((LPWSTR)L"ntdll.dll", "NtQuerySystemInformation");

	auto* func_bytes = reinterpret_cast<BYTE*>(func);

	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] NtQuerySystemInformation" << std::endl;
	}
	else
	{
		std::cout << "[OK] NtQuerySystemInformation" << std::endl;
	}
}

inline void scyllahide_nt_query_information_process()
{
	const auto func = MemoryMaster::WinUtils::GetFunctionPEB((LPWSTR)L"ntdll.dll", "NtQueryInformationProcess");

	auto* func_bytes = reinterpret_cast<BYTE*>(func);

	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] NtQueryInformationProcess" << std::endl;
	}
	else
	{
		std::cout << "[OK] NtQueryInformationProcess" << std::endl;
	}
}

inline void scyllahide_nt_query_object()
{
	const auto func = MemoryMaster::WinUtils::GetFunctionPEB((LPWSTR)L"ntdll.dll", "NtQueryObject");

	auto* func_bytes = reinterpret_cast<BYTE*>(func);

	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] NtQueryObject" << std::endl;
	}
	else
	{
		std::cout << "[OK] NtQueryObject" << std::endl;
	}
}

inline void scyllahide_nt_yield_execution()
{
	const auto func = MemoryMaster::WinUtils::GetFunctionPEB((LPWSTR)L"ntdll.dll", "NtYieldExecution");

	auto* func_bytes = reinterpret_cast<BYTE*>(func);

	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] NtYieldExecution" << std::endl;
	}
	else
	{
		std::cout << "[OK] NtYieldExecution" << std::endl;
	}
}

inline void scyllahide_nt_create_thread_ex()
{
	const auto func = MemoryMaster::WinUtils::GetFunctionPEB((LPWSTR)L"ntdll.dll", "NtCreateThreadEx");

	auto* func_bytes = reinterpret_cast<BYTE*>(func);

	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] NtCreateThreadEx" << std::endl;
	}
	else
	{
		std::cout << "[OK] NtCreateThreadEx" << std::endl;
	}
}

inline void scyllahide_nt_set_debug_filter_state()
{
	const auto func = MemoryMaster::WinUtils::GetFunctionPEB((LPWSTR)L"ntdll.dll", "NtSetDebugFilterState");

	auto* func_bytes = reinterpret_cast<BYTE*>(func);
	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] NtSetDebugFilterState" << std::endl;
	}
	else
	{
		std::cout << "[OK] NtSetDebugFilterState" << std::endl;
	}
}

inline void scyllahide_nt_close()
{
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"ntdll.dll"));
	const auto func = get_function(p, "NtClose");

	auto* func_bytes = reinterpret_cast<BYTE*>(func);

	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] NtClose" << std::endl;
	}
	else
	{
		std::cout << "[OK] NtClose" << std::endl;
	}
}

inline void scyllahide_nt_query_performance_counter()
{
	const auto func = MemoryMaster::WinUtils::GetFunctionPEB((LPWSTR)L"ntdll.dll", "NtQueryPerformanceCounter");
	auto* func_bytes = reinterpret_cast<BYTE*>(func);

	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] NtQueryPerformanceCounter" << std::endl;
	}
	else
	{
		std::cout << "[OK] NtQueryPerformanceCounter" << std::endl;
	}
}

inline void scyllahide_nt_get_context_thread()
{
	const auto func = MemoryMaster::WinUtils::GetFunctionPEB((LPWSTR)L"ntdll.dll", "NtGetContextThread");

	auto* func_bytes = reinterpret_cast<BYTE*>(func);

	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] NtGetContextThread" << std::endl;
	}
	else
	{
		std::cout << "[OK] NtGetContextThread" << std::endl;
	}
}

inline void scyllahide_get_tick_count()
{
	const auto func = MemoryMaster::WinUtils::GetFunctionPEB((LPWSTR)L"kernel32.dll", "GetTickCount");

	auto* func_bytes = reinterpret_cast<BYTE*>(func);
	BYTE trampoline_function[3] = {0x48, 0xFF, 0x25};

	if (memcmp(func_bytes, trampoline_function, 3) == 0)
	{
		const auto function_pointer = *reinterpret_cast<DWORD*>(func_bytes + 0x3);
		func_bytes = *reinterpret_cast<BYTE**>(func_bytes + function_pointer + 0x7);
	}

	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] GetTickCount" << std::endl;
	}
	else
	{
		std::cout << "[OK] GetTickCount" << std::endl;
	}
}

inline void scyllahide_get_tick_count64()
{
	const auto func = MemoryMaster::WinUtils::GetFunctionPEB((LPWSTR)L"kernel32.dll", "GetTickCount64");

	auto* func_bytes = reinterpret_cast<BYTE*>(func);
	BYTE trampoline_function[3] = {0x48, 0xFF, 0x25};

	if (memcmp(func_bytes, trampoline_function, 3) == 0)
	{
		const auto function_pointer = *reinterpret_cast<DWORD*>(func_bytes + 0x3);
		func_bytes = *reinterpret_cast<BYTE**>(func_bytes + function_pointer + 0x7);
	}

	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] GetTickCount64" << std::endl;
	}
	else
	{
		std::cout << "[OK] GetTickCount64" << std::endl;
	}
}

inline void scyllahide_output_debug_string_a()
{
	const auto func = MemoryMaster::WinUtils::GetFunctionPEB((LPWSTR)L"kernel32.dll", "OutputDebugStringA");

	auto* func_bytes = reinterpret_cast<BYTE*>(func);
	BYTE trampoline_function[3] = {0x48, 0xFF, 0x25};

	if (memcmp(func_bytes, trampoline_function, 3) == 0)
	{
		const auto function_pointer = *reinterpret_cast<DWORD*>(func_bytes + 0x3);
		func_bytes = *reinterpret_cast<BYTE**>(func_bytes + function_pointer + 0x7);
	}

	if (is_hooked(func_bytes))
	{
		std::cout << "[DETECTED] OutputDebugStringA" << std::endl;
	}
	else
	{
		std::cout << "[OK] OutputDebugStringA" << std::endl;
	}
}
