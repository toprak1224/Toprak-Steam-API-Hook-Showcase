#include <windows.h>

class ISteamApps {
public:
    virtual bool BIsDlcInstalled(unsigned int appID) = 0;
    virtual int GetDLCCount() = 0;
};

typedef bool(__thiscall* BIsDlcInstalled_t)(ISteamApps* thisptr, unsigned int appID);
BIsDlcInstalled_t Original_BIsDlcInstalled = nullptr;

bool __fastcall Hooked_BIsDlcInstalled(ISteamApps* thisptr, void* edx, unsigned int appID) {
    return Original_BIsDlcInstalled(thisptr, appID);
}

void SetupHooks() {
    HMODULE hSteamAPI = GetModuleHandleA("steamclient64.dll");
    while (!hSteamAPI) {
        Sleep(100);
        hSteamAPI = GetModuleHandleA("steamclient64.dll");
    }

    uintptr_t pFunction = 0x00000000; 

    // MH_Initialize();
    // MH_CreateHook((void*)pFunction, &Hooked_BIsDlcInstalled, (void**)&Original_BIsDlcInstalled);
    // MH_EnableHook(MH_ALL_HOOKS);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)SetupHooks, nullptr, 0, nullptr);
    }
    return TRUE;
}
