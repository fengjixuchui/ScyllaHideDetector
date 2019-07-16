#include "pch.h"
#include "SigFinder.h"

MemoryMaster::SigFinder::SigFinder(void* region, size_t regionSize) {
	this->region = region;
	this->regionSize = regionSize;
}

MemoryMaster::SigFinder::SigFinder(const char* moduleName) {
	MODULE mdl;
	MemoryMaster::WinUtils::GetModule(moduleName, &mdl);

	this->region = (void*)mdl.base;
	this->regionSize = mdl.size;
}

void MemoryMaster::SigFinder::Configure(const char* pattern, const char* mask) {
	this->mask = mask;
	this->pattern = pattern;
}

bool MemoryMaster::SigFinder::MaskCompare(const char* pattern, const char* mask, char* data) {

	for (size_t i = 0; i < strlen(mask); i++) {
		if (mask[i] == '?') continue;

		if (data[i] != pattern[i]) {
			return false;
		}
	}

	return true;
}

void* MemoryMaster::SigFinder::Find() {
	return this->Find(this->pattern, this->mask);
}

void* MemoryMaster::SigFinder::Find(const char* pattern, const char* mask) {
	size_t sizeOfPattern = strlen(mask);
	size_t endOfRegion = ((size_t)this->region + this->regionSize);

	size_t position = (size_t)this->region;

	while (position < endOfRegion) {
		if (this->MaskCompare(pattern, mask, (char*)position)) {
			return (void*)position;
		}

		position++;
	}

	return nullptr;
}