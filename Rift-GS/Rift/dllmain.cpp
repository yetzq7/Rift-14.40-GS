// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"
#include "Hooks.h"

void Main()
{
    AllocConsole();
    FILE* File = nullptr;
    freopen_s(&File, "CONOUT$", "w+", stdout);
    Sleep(5000);
    MH_Initialize();

    Hook(ImageBase + Addresses::GetNetMode, ReturnTrue, nullptr);

    *reinterpret_cast<bool*>((ImageBase + Addresses::GIsClient)) = false;
    *reinterpret_cast<bool*>((ImageBase + Addresses::GIsClient + 1)) = true;

	for (auto& NullFunc : Addresses::NullFuncs)
    {
		Hook(ImageBase + NullFunc, ReturnHook, nullptr);
    }   

	Hook(ImageBase + Addresses::TickFlush, TickFlush, (void**)&TickFlush_OG);

	UEngine::GetEngine()->GameViewport->World->OwningGameInstance->LocalPlayers.Remove(0);
    UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"open Apollo_Terrain", nullptr);
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

