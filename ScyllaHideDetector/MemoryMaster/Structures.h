#pragma once

#include "pch.h"

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