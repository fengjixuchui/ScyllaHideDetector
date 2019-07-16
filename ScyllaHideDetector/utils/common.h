#pragma once
#include <Windows.h>
#include <stdio.h>

//typedef enum _THREAD_INFORMATION_CLASS_NEW {
//	ThreadBasicInformation,
//	ThreadTimes,
//	ThreadPriority,
//	ThreadBasePriority,
//	ThreadAffinityMask,
//	ThreadImpersonationToken,
//	ThreadDescriptorTableEntry,
//	ThreadEnableAlignmentFaultFixup,
//	ThreadEventPair,
//	ThreadQuerySetWin32StartAddress,
//	ThreadZeroTlsCell,
//	ThreadPerformanceCount,
//	ThreadAmILastThread,
//	ThreadIdealProcessor,
//	ThreadPriorityBoost,
//	ThreadSetTlsArrayAddress,
//	ThreadIsIoPending,
//	ThreadHideFromDebugger
//} THREAD_INFORMATION_CLASS_NEW, * PTHREAD_INFORMATION_CLASS_NEW;

typedef NTSTATUS (*NtSetInformationThread_t)(
	IN HANDLE               ThreadHandle,
	IN THREAD_INFORMATION_CLASS ThreadInformationClass,
	IN PVOID                ThreadInformation,
	IN ULONG                ThreadInformationLength
);
typedef NTSTATUS(*NtSetInformationProcess_t)(
	IN HANDLE               ProcessHandle,
	IN THREAD_INFORMATION_CLASS ProcessInformationClass,
	IN PVOID                ProcessInformation,
	IN ULONG                ProcessInformationLength
	);
typedef NTSTATUS(*NtQuerySystemInformation_t)(
	IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
	OUT PVOID                   SystemInformation,
	IN ULONG                    SystemInformationLength,
	OUT PULONG                  ReturnLength
	);
typedef NTSTATUS(*NtQueryInformationProcess_t)(
	IN HANDLE               ProcessHandle,
	IN SYSTEM_INFORMATION_CLASS ProcessInformationClass,
	OUT PVOID               ProcessInformation,
	IN ULONG                ProcessInformationLength,
	OUT PULONG              ReturnLength
	);
typedef NTSTATUS(*NtQueryObject_t)(
	IN HANDLE               ObjectHandle,
	IN _OBJECT_INFORMATION_CLASS ObjectInformationClass,
	OUT PVOID               ObjectInformation,
	IN ULONG                Length,
	OUT PULONG              ResultLength
	);
typedef NTSTATUS(*NtYieldExecution_t)();
typedef NTSTATUS(*NtCreateThreadEx_t)();
typedef NTSTATUS(*NtSetDebugFilterState_t)(
	ULONG 	ComponentId,
	ULONG 	Level,
	BOOLEAN 	State
	);
typedef NTSTATUS(*NtQueryPerformanceCounter_t)(
	OUT PLARGE_INTEGER      PerformanceCounter,
	OUT PLARGE_INTEGER      PerformanceFrequency OPTIONAL
	);
typedef NTSTATUS(*NtGetContextThread_t)(
	IN HANDLE               ThreadHandle,
	OUT PCONTEXT            pContext
	);
typedef DWORD(WINAPI* t_GetTickCount)(void);
typedef ULONGLONG(WINAPI* t_GetTickCount64)(void);
typedef DWORD(WINAPI* t_OutputDebugStringA)(LPCSTR lpOutputString);

/*
	Объявляем незадокументрированные структуры
 */

//typedef struct _UNICODE_STRING_WOW64 {
//	USHORT Length;
//	USHORT MaximumLength;
//	PVOID64 Buffer;
//} UNICODE_STRING;

typedef struct {
	LIST_ENTRY Orders[3];
	PVOID64    base;
	PVOID64      EntryPoint;
	UINT       Size;
	UNICODE_STRING dllFullPath;
	UNICODE_STRING dllname;
} LDR_ENTRY;

// ---------------------------

/*
	Функция получения базового адреса модуля,
		который выгружен в наше виртуальное адресное пространство
 */
PVOID64 GetModuleBase(LPWSTR moduleName) {
	// читаем из сегментного регистра gs со смещением 0x60 (в x64 процессе загрузчик программ винды в контексте процесса в gs пишет Thread Environment Block)
	// а если взять со смещением 0x60 (параметр структуры Thread Environment Block) - то будет PEB (Process Environment Block)
	UINT64 peb = (UINT64)__readgsqword(0x60);

	// читаем из структуры PEB структуру LDR
	UINT64 moduleListAddr = *(UINT64*)(peb + 0x18);

	// тут начинается список загруженных в процесс модулей (LinkedList)
	PVOID64 start = *(PVOID64*)(moduleListAddr + 0x18);

	// Берем первый LDR_ENTRY
	LDR_ENTRY * mod = (LDR_ENTRY*)start;

	// Берем ссылку на след элемент после него (LinkedList жеж)
	mod = (LDR_ENTRY*)mod->Orders[0].Flink;

	// идем, пока не пришли к началу
	while ((UINT64)start != (UINT64)mod) {

		if (mod->base != NULL)
		{

			// Это нужный нам модуль?
			if (!lstrcmpiW((LPCWSTR)mod->dllname.Buffer, moduleName))
			{

				// Да!
				return mod->base;
			}
		}

		// Идем далее
		mod = (LDR_ENTRY*)mod->Orders[0].Flink;
	}

	return 0;
}

// тут просто парсим экспорт из PE заголовков загруженного модуля
UINT64 GetFunction(UINT64 base, LPCSTR function) {

	// пропускаем лишнее
	IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)base;
	IMAGE_NT_HEADERS64* ntHeaders = (IMAGE_NT_HEADERS64*)(base + dosHeader->e_lfanew);

	// получаем таблицу экспорта
	IMAGE_EXPORT_DIRECTORY * exportTable =
		(IMAGE_EXPORT_DIRECTORY*)(base +
			ntHeaders->OptionalHeader.DataDirectory[0].VirtualAddress);


	// получаем ее элементы (идентифицируются по именам и ordinal - почитать можешь подробнее в нетике)
	DWORD * functions = (DWORD*)(base + exportTable->AddressOfFunctions);
	WORD * ords = (WORD*)(base + exportTable->AddressOfNameOrdinals);
	DWORD * names = (DWORD*)(base + exportTable->AddressOfNames);

	// проходимся по именам
	for (int i = 0; i < exportTable->NumberOfNames; i++) {
		char* data = (char*)(base + (UINT64)names[i]);

		// это нужное нам имя?
		if (lstrcmpA(function, data) == 0) {

			// да, берем функцию с нужным индексом
			return base + (UINT64)functions[ords[i]];
		}
	}

	return 0;
}

bool IsHooked(BYTE* func) {
	return (func[0] == 0x90 || func[0] == 0xE9);
}
