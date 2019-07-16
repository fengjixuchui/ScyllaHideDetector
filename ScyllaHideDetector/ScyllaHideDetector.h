#pragma once

void Scyllahide_NtSetInformationThread()
{
    auto p = (UINT64)GetModuleBase((LPWSTR)L"ntdll.dll");
    UINT64 func = GetFunction(p, "NtSetInformationThread");

    auto ourNtSetInformationThread = (NtSetInformationThread_t)func;

    bool hide = true;

    ourNtSetInformationThread(GetCurrentThread(), (THREAD_INFORMATION_CLASS)ThreadHideFromDebugger, &hide, 1);

    auto funcBytes = (BYTE*)(func);

    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] NtSetInformationThread" << std::endl;
    }
    else {
        std::cout << "[OK] NtSetInformationThread" << std::endl;
    }
}

void Scyllahide_NtSetInformationProcess()
{
    auto p = (UINT64)GetModuleBase((LPWSTR)L"ntdll.dll");
    UINT64 func = GetFunction(p, "NtSetInformationProcess");

    auto ourNtSetInformationProcess = (NtSetInformationProcess_t)func;

    bool hide = true;

    ourNtSetInformationProcess(GetCurrentThread(), (THREAD_INFORMATION_CLASS)ThreadHideFromDebugger, &hide, 1);

    auto* funcBytes = (BYTE*)(func);

    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] NtSetInformationProcess" << std::endl;
    }
    else {
        std::cout << "[OK] NtSetInformationProcess" << std::endl;
    }
}

void Scyllahide_NtQuerySystemInformation()
{
    auto p = (UINT64)GetModuleBase((LPWSTR)L"ntdll.dll");
    UINT64 func = GetFunction(p, "NtQuerySystemInformation");

    auto ourNtQuerySystemInformation = (NtQuerySystemInformation_t)func;

    bool hide = true;

    ourNtQuerySystemInformation(SystemProcessInformation, &hide, 1, nullptr);

    auto* funcBytes = (BYTE*)(func);

    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] NtQuerySystemInformation" << std::endl;
    }
    else {
        std::cout << "[OK] NtQuerySystemInformation" << std::endl;
    }
}

void Scyllahide_NtQueryInformationProcess()
{
    auto p = (UINT64)GetModuleBase((LPWSTR)L"ntdll.dll");
    UINT64 func = GetFunction(p, "NtQueryInformationProcess");

    auto ourNtQueryInformationProcess = (NtQueryInformationProcess_t)func;

    bool hide = true;

    ourNtQueryInformationProcess(GetCurrentThread(), SystemProcessInformation, &hide, 1, nullptr);

    auto* funcBytes = (BYTE*)(func);

    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] NtQueryInformationProcess" << std::endl;
    }
    else {
        std::cout << "[OK] NtQueryInformationProcess" << std::endl;
    }
}

void Scyllahide_NtQueryObject()
{

    auto p = (UINT64)GetModuleBase((LPWSTR)L"ntdll.dll");
    UINT64 func = GetFunction(p, "NtQueryObject");

    auto ourNtQueryObject = (NtQueryObject_t)func;

    bool hide = true;

    ourNtQueryObject(GetCurrentThread(), MaxObjectInfoClass, &hide, 1, nullptr);

    auto* funcBytes = (BYTE*)(func);

    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] NtQueryObject" << std::endl;
    }
    else {
        std::cout << "[OK] NtQueryObject" << std::endl;
    }
}

void Scyllahide_NtYieldExecution()
{
    auto p = (UINT64)GetModuleBase((LPWSTR)L"ntdll.dll");
    UINT64 func = GetFunction(p, "NtYieldExecution");

    auto ourNtYieldExecution = (NtYieldExecution_t)func;

    ourNtYieldExecution();

    auto* funcBytes = (BYTE*)(func);

    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] NtYieldExecution" << std::endl;
    }
    else {
        std::cout << "[OK] NtYieldExecution" << std::endl;
    }
}

void Scyllahide_NtCreateThreadEx()
{
    auto p = (UINT64)GetModuleBase((LPWSTR)L"ntdll.dll");
    UINT64 func = GetFunction(p, "NtCreateThreadEx");

    auto ourNtCreateThreadEx = (NtCreateThreadEx_t)func;

    bool hide = true;

    ourNtCreateThreadEx();

    auto* funcBytes = (BYTE*)(func);

    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] NtCreateThreadEx" << std::endl;
    }
    else {
        std::cout << "[OK] NtCreateThreadEx" << std::endl;
    }
}

void Scyllahide_NtSetDebugFilterState()
{
    auto p = (UINT64)GetModuleBase((LPWSTR)L"ntdll.dll");
    UINT64 func = GetFunction(p, "NtSetDebugFilterState");

    auto ourNtSetDebugFilterState = (NtSetDebugFilterState_t)func;

    bool hide = true;

    ourNtSetDebugFilterState(0, 0, false);

    auto* funcBytes = (BYTE*)(func);
    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] NtSetDebugFilterState" << std::endl;
    }
    else {
        std::cout << "[OK] NtSetDebugFilterState" << std::endl;
    }
}

void Scyllahide_NtClose()
{
    auto p = (UINT64)GetModuleBase((LPWSTR)L"ntdll.dll");
    UINT64 func = GetFunction(p, "NtClose");

    auto* funcBytes = (BYTE*)(func);

    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] NtClose" << std::endl;
    }
    else {
        std::cout << "[OK] NtClose" << std::endl;
    }
}

void Scyllahide_NtQueryPerformanceCounter()
{
    auto p = (UINT64)GetModuleBase((LPWSTR)L"ntdll.dll");
    UINT64 func = GetFunction(p, "NtQueryPerformanceCounter");

    auto ourNtQueryPerformanceCounter = (NtQueryPerformanceCounter_t)func;

    bool hide = true;
    LARGE_INTEGER counter;
    ourNtQueryPerformanceCounter(&counter, nullptr);

    auto* funcBytes = (BYTE*)(func);
    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] NtQueryPerformanceCounter" << std::endl;
    }
    else {
        std::cout << "[OK] NtQueryPerformanceCounter" << std::endl;
    }
}

void Scyllahide_NtGetContextThread()
{
    auto p = (UINT64)GetModuleBase((LPWSTR)L"ntdll.dll");
    UINT64 func = GetFunction(p, "NtGetContextThread");

    auto ourNtGetContextThread = (NtGetContextThread_t)func;
    CONTEXT ctx;
    ourNtGetContextThread(GetCurrentThread(), &ctx);

    auto* funcBytes = (BYTE*)(func);
    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] NtGetContextThread" << std::endl;
    }
    else {
        std::cout << "[OK] NtGetContextThread" << std::endl;
    }
}

void Scyllahide_GetTickCount()
{
    auto p = (UINT64)GetModuleBase((LPWSTR)L"kernel32.dll");
    UINT64 func = GetFunction(p, "GetTickCount");

    auto ourGetTickCount = (t_GetTickCount)func; // вот так
    ourGetTickCount();

    auto* funcBytes = (BYTE*)(func);
    BYTE TrampolineFunction[3] = { 0x48, 0xFF, 0x25 };

    if (memcmp(funcBytes, TrampolineFunction, 3) == 0) {
        DWORD functionPointer = *(DWORD*)(funcBytes + 0x3);
        funcBytes = *(BYTE**)(funcBytes + functionPointer + 0x7);
    }

    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] GetTickCount" << std::endl;
    }
    else {
        std::cout << "[OK] GetTickCount" << std::endl;
    }
}

void Scyllahide_GetTickCount64()
{
    auto p = (UINT64)GetModuleBase((LPWSTR)L"kernel32.dll");
    auto func = GetFunction(p, "GetTickCount64");

    auto ourGetTickCount64 = (t_GetTickCount64)func;
    ourGetTickCount64();

    auto* funcBytes = (BYTE*)(func);
    BYTE TrampolineFunction[3] = { 0x48, 0xFF, 0x25 };

    if (memcmp(funcBytes, TrampolineFunction, 3) == 0) {
        DWORD functionPointer = *(DWORD*)(funcBytes + 0x3);
        funcBytes = *(BYTE**)(funcBytes + functionPointer + 0x7);
    }

    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] GetTickCount64" << std::endl;
    }
    else {
        std::cout << "[OK] GetTickCount64" << std::endl;
    }
}

void Scyllahide_OutputDebugStringA()
{

    auto p = (UINT64)GetModuleBase((LPWSTR)L"kernel32.dll");
    UINT64 func = GetFunction(p, "OutputDebugStringA");

    auto ourOutputDebugStringA = (t_OutputDebugStringA)func;
    ourOutputDebugStringA("hello");

    auto* funcBytes = (BYTE*)(func);
    BYTE TrampolineFunction[3] = { 0x48, 0xFF, 0x25 };

    if (memcmp(funcBytes, TrampolineFunction, 3) == 0) {
        DWORD functionPointer = *(DWORD*)(funcBytes + 0x3);
        funcBytes = *(BYTE**)(funcBytes + functionPointer + 0x7);
    }

    if (IsHooked(funcBytes)) {
        std::cout << "[DETECTED] OutputDebugStringA" << std::endl;
    }
    else {
        std::cout << "[OK] OutputDebugStringA" << std::endl;
    }
}

