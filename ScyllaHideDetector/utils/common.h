#pragma once

#include <Windows.h>

typedef NTSTATUS (*NtSetInformationThread_t)(
	IN HANDLE ThreadHandle,
	IN THREAD_INFORMATION_CLASS ThreadInformationClass,
	IN PVOID ThreadInformation,
	IN ULONG ThreadInformationLength);

typedef NTSTATUS (*NtSetInformationProcess_t)(
	IN HANDLE ProcessHandle,
	IN THREAD_INFORMATION_CLASS ProcessInformationClass,
	IN PVOID ProcessInformation,
	IN ULONG ProcessInformationLength);

typedef NTSTATUS (*NtQuerySystemInformation_t)(
	IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
	OUT PVOID SystemInformation,
	IN ULONG SystemInformationLength,
	OUT PULONG ReturnLength);

typedef NTSTATUS (*NtQueryInformationProcess_t)(
	IN HANDLE ProcessHandle,
	IN SYSTEM_INFORMATION_CLASS ProcessInformationClass,
	OUT PVOID ProcessInformation,
	IN ULONG ProcessInformationLength,
	OUT PULONG ReturnLength);

typedef NTSTATUS (*NtQueryObject_t)(
	IN HANDLE ObjectHandle,
	IN _OBJECT_INFORMATION_CLASS ObjectInformationClass,
	OUT PVOID ObjectInformation,
	IN ULONG Length,
	OUT PULONG ResultLength);

typedef NTSTATUS (*NtYieldExecution_t)();

typedef NTSTATUS (*NtCreateThreadEx_t)();

typedef NTSTATUS (*NtSetDebugFilterState_t)(
	ULONG ComponentId,
	ULONG Level,
	BOOLEAN State);

typedef NTSTATUS (*NtQueryPerformanceCounter_t)(
	OUT PLARGE_INTEGER PerformanceCounter,
	OUT PLARGE_INTEGER PerformanceFrequency OPTIONAL);

typedef NTSTATUS (*NtGetContextThread_t)(
	IN HANDLE ThreadHandle,
	OUT PCONTEXT pContext);

typedef DWORD (WINAPI* t_GetTickCount)();

typedef ULONGLONG (WINAPI* t_GetTickCount64)();

typedef DWORD (WINAPI* t_OutputDebugStringA)(LPCSTR lpOutputString);

/*
	Объявляем незадокументрированные структуры
 */

typedef struct
{
	LIST_ENTRY Orders[3];
	PVOID64 base;
	PVOID64 EntryPoint;
	UINT Size;
	UNICODE_STRING dllFullPath;
	UNICODE_STRING dllname;
} LDR_ENTRY;

/*
	Функция получения базового адреса модуля,
		который выгружен в наше виртуальное адресное пространство
 */
inline PVOID64 get_module_base(const LPWSTR module_name)
{
	// читаем из сегментного регистра gs со смещением 0x60 (в x64 процессе загрузчик программ винды в контексте процесса в gs пишет Thread Environment Block)
	// а если взять со смещением 0x60 (параметр структуры Thread Environment Block) - то будет PEB (Process Environment Block)
	const auto peb = static_cast<UINT64>(__readgsqword(0x60));

	// читаем из структуры PEB структуру LDR
	const auto module_list_addr = *reinterpret_cast<UINT64*>(peb + 0x18);

	// тут начинается список загруженных в процесс модулей (LinkedList)
	auto start = *reinterpret_cast<PVOID64*>(module_list_addr + 0x18);

	// Берем первый LDR_ENTRY
	auto* mod = static_cast<LDR_ENTRY*>(start);

	// Берем ссылку на след элемент после него (LinkedList жеж)
	mod = reinterpret_cast<LDR_ENTRY*>(mod->Orders[0].Flink);

	// идем, пока не пришли к началу
	while (reinterpret_cast<UINT64>(start) != reinterpret_cast<UINT64>(mod))
	{
		if (mod->base != nullptr)
		{
			// Это нужный нам модуль?
			if (!lstrcmpiW(static_cast<LPCWSTR>(mod->dllname.Buffer), module_name))
			{
				// Да!
				return mod->base;
			}
		}

		// Идем далее
		mod = reinterpret_cast<LDR_ENTRY*>(mod->Orders[0].Flink);
	}

	return nullptr;
}

// тут просто парсим экспорт из PE заголовков загруженного модуля
inline UINT64 get_function(const UINT64 base, const LPCSTR function)
{
	// пропускаем лишнее
	auto* dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
	auto* nt_headers = reinterpret_cast<IMAGE_NT_HEADERS64*>(base + dos_header->e_lfanew);

	// получаем таблицу экспорта
	auto* export_table = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(base + nt_headers->OptionalHeader.DataDirectory[0].
		VirtualAddress);

	// получаем ее элементы (идентифицируются по именам и ordinal - почитать можешь подробнее в нетике)
	auto* functions = reinterpret_cast<DWORD*>(base + export_table->AddressOfFunctions);
	const auto ords = reinterpret_cast<WORD*>(base + export_table->AddressOfNameOrdinals);
	auto* names = reinterpret_cast<DWORD*>(base + export_table->AddressOfNames);

	// проходимся по именам
	for (auto i = 0; i < static_cast<int>(export_table->NumberOfNames); i++)
	{
		const auto data = reinterpret_cast<char*>(base + static_cast<UINT64>(names[i]));

		// это нужное нам имя?
		if (lstrcmpA(function, data) == 0)
		{
			// да, берем функцию с нужным индексом
			return base + static_cast<UINT64>(functions[ords[i]]);
		}
	}

	return 0;
}

inline bool is_hooked(BYTE* func)
{
	return func[0] == 0x90 || func[0] == 0xE9;
}
