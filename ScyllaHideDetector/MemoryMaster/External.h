#pragma once

namespace MemoryMaster {
	namespace External {
		class Injector {
		public:
			static InjectStatus InjectDLL(const char* dll, const char* processName);
			static InjectStatus InjectDLL(const char* dll, DWORD pid);
		};
	}
}