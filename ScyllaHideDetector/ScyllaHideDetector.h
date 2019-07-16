#pragma once
#include "utils/common.h"

inline void scyllahide_nt_set_information_thread()
{
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"ntdll.dll"));
	const auto func = get_function(p, "NtSetInformationThread");

	const auto our_nt_set_information_thread = reinterpret_cast<nt_set_information_thread_t>(func);

	auto hide = true;

	our_nt_set_information_thread(GetCurrentThread(), static_cast<THREAD_INFORMATION_CLASS>(ThreadHideFromDebugger), &hide, 1);

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
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"ntdll.dll"));
	const auto func = get_function(p, "NtSetInformationProcess");

	const auto our_nt_set_information_process = reinterpret_cast<nt_set_information_process_t>(func);

	auto hide = true;

	our_nt_set_information_process(GetCurrentThread(), static_cast<THREAD_INFORMATION_CLASS>(ThreadHideFromDebugger), &hide, 1);

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
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"ntdll.dll"));
	const auto func = get_function(p, "NtQuerySystemInformation");

	const auto our_nt_query_system_information = reinterpret_cast<nt_query_system_information_t>(func);

	auto hide = true;

	our_nt_query_system_information(SystemProcessInformation, &hide, 1, nullptr);

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
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"ntdll.dll"));
	const auto func = get_function(p, "NtQueryInformationProcess");

	const auto our_nt_query_information_process = reinterpret_cast<nt_query_information_process_t>(func);

	auto hide = true;

	our_nt_query_information_process(GetCurrentThread(), SystemProcessInformation, &hide, 1, nullptr);

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
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"ntdll.dll"));
	const auto func = get_function(p, "NtQueryObject");

	const auto our_nt_query_object = reinterpret_cast<nt_query_object_t>(func);

	auto hide = true;

	our_nt_query_object(GetCurrentThread(), MaxObjectInfoClass, &hide, 1, nullptr);

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
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"ntdll.dll"));
	const auto func = get_function(p, "NtYieldExecution");

	const auto our_nt_yield_execution = reinterpret_cast<nt_yield_execution_t>(func);

	our_nt_yield_execution();

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
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"ntdll.dll"));
	const auto func = get_function(p, "NtCreateThreadEx");

	const auto our_nt_create_thread_ex = reinterpret_cast<nt_create_thread_ex_t>(func);

	our_nt_create_thread_ex();

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
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"ntdll.dll"));
	const auto func = get_function(p, "NtSetDebugFilterState");

	const auto our_nt_set_debug_filter_state = reinterpret_cast<nt_set_debug_filter_state_t>(func);

	our_nt_set_debug_filter_state(0, 0, false);

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
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"ntdll.dll"));
	const auto func = get_function(p, "NtQueryPerformanceCounter");

	const auto our_nt_query_performance_counter = reinterpret_cast<nt_query_performance_counter_t>(func);

	LARGE_INTEGER counter;
	our_nt_query_performance_counter(&counter, nullptr);

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
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"ntdll.dll"));
	const auto func = get_function(p, "NtGetContextThread");

	const auto our_nt_get_context_thread = reinterpret_cast<nt_get_context_thread_t>(func);
	CONTEXT ctx;
	our_nt_get_context_thread(GetCurrentThread(), &ctx);

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
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"kernel32.dll"));
	const auto func = get_function(p, "GetTickCount");

	const auto our_get_tick_count = reinterpret_cast<get_tick_count_t>(func);
	our_get_tick_count();

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
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"kernel32.dll"));
	const auto func = get_function(p, "GetTickCount64");

	const auto our_get_tick_count64 = reinterpret_cast<get_tick_count64_t>(func);
	our_get_tick_count64();

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
	const auto p = reinterpret_cast<UINT64>(get_module_base((LPWSTR)L"kernel32.dll"));
	const auto func = get_function(p, "OutputDebugStringA");

	const auto our_output_debug_string_a = reinterpret_cast<output_debug_string_a_t>(func);
	our_output_debug_string_a("hello");

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
