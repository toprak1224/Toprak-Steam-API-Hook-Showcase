#include <windows.h>
#include <string>

void* pRealXInputGetState = nullptr;
void* pRealXInputSetState = nullptr;

void LoadRealDLL() {
    char sysDir[MAX_PATH];
    GetSystemDirectoryA(sysDir, MAX_PATH);
    std::string realDLLPath = std::string(sysDir) + "\\xinput1_4.dll";

    HMODULE hRealModule = LoadLibraryA(realDLLPath.c_str());
    if (hRealModule) {
        pRealXInputGetState = (void*)GetProcAddress(hRealModule, "XInputGetState");
        pRealXInputSetState = (void*)GetProcAddress(hRealModule, "XInputSetState");
    }
}

DWORD WINAPI Fake_XInputGetState(DWORD dwUserIndex, void* pState) {
    if (!pRealXInputGetState) LoadRealDLL();
    return ((DWORD(WINAPI*)(DWORD, void*))pRealXInputGetState)(dwUserIndex, pState);
}

void LoadPayload() {
    char processPath[MAX_PATH];
    GetModuleFileNameA(NULL, processPath, MAX_PATH);
    
    const char* exeName = strrchr(processPath, '\\');
    exeName = exeName ? exeName + 1 : processPath;
    
    if (_stricmp(exeName, "steam.exe") == 0) {
        LoadLibraryA("toprakcracker.dll");
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        LoadRealDLL();
        LoadPayload();
    }
    return TRUE;
}
