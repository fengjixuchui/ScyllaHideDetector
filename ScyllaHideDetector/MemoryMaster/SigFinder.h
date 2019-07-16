#pragma once

#include "WinUtils.h"

namespace MemoryMaster {
	class SigFinder {
	private:

		const char* mask = nullptr;
		const char* pattern = nullptr;

		void* region;
		size_t regionSize;

		bool MaskCompare(const char* pattern, const char* mask, char* data);
		
	public:

		SigFinder(void* region, size_t regionSize);
		SigFinder(const char* moduleName);

		void Configure(const char* pattern, const char* mask);

		void* Find();
		void* Find(const char* pattern, const char* mask);
	};
}
