// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"

void Main()
{
    AllocConsole();
    FILE* File = nullptr;
    freopen_s(&File, "CONOUTS", "n+", stdout);
    Sleep(5000);

    UKisntSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"open Apollo_Terrain", nullptr);
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        std::thread(Main).detach();
        break;
    }
    return TRUE;
}

