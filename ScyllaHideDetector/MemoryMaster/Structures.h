#pragma once

#include "pch.h"
#include "../utils/ntdll.h"
enum InjectStatus {
	ERR_OPEN_PROCESS,
	ERR_WRITE_DLL_NAME,
	ERR_GET_LOADLIBRARY,
	SUCCESS
};

typedef struct _MODULE {
	size_t size;
	void* base;
} MODULE, *PMODULE;


//typedef struct _UNICODE_STRING
//{
//	USHORT Length;
//	USHORT MaximumLength;
//	PWSTR Buffer;
//} UNICODE_STRING, * PUNICODE_STRING;
//typedef const UNICODE_STRING* PCUNICODE_STRING;

typedef struct
{
	LIST_ENTRY Orders[3];
	PVOID Base;
	PVOID EntryPoint;
	UINT Size;
	UNICODE_STRING DllFullPath;
	UNICODE_STRING DllName;
} LDR_ENTRY;

#ifdef _WIN64
typedef UINT64 PTR;
#else
typedef UINT32 PTR;
#endif