#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <thread>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "SDK/SDK.hpp"
using namespace SDK;
#include "MinHook.h"  
#include "SDK/UnrealContainers.hpp"
#include "SDK/SDK/Basic.hpp" 

inline uint64 ImageBase = uint64(GetModuleHandle(0));

namespace Addresses {
    inline uint64_t Step = 0x1b52f60;
    inline uint64_t StepExplicitProperty = 0x1b52f90;
    inline uint64_t CreateNetDriver = 0x2c69d8a;
    inline uint64_t InitListen = 0x4659d0;
    inline uint64_t SetWorld = 0x29fbce0;
    inline uint64_t GetNetMode = 0x2cd6a40;
    inline uint64_t TickFlush = 0x29fc860;
    inline uint64_t ServerReplicateActors = 0x1374fb0;
    inline uint64_t GetMaxTickRate = 0x2c75fe0;
    inline uint64_t DispatchRequest = 0xa7d080;
    inline uint64_t Realloc = 0x18d1060;
    inline uint64_t StaticFindObject = 0x1b51790;
    inline uint64_t StaticLoadObject = 0x1b528f0;
    inline uint64_t GIsClient = 0x5a8ab39;
    inline uint64_t GameSessionPatch = 0xdb564d;
    inline uint64_t EncryptionPatch = 0x2cd94ae;
    inline std::vector<uint64_t> NullFuncs = { 0x24df7e0, 0x1061160, 0x28cade0 };
    inline std::vector<uint64_t> RetTrueFuncs = {  };
};

namespace Funcs {
    inline auto CreateNetDriver = (SDK::UNetDriver * (*)(SDK::UEngine*, SDK::UWorld*, SDK::FName)) (ImageBase + Addresses::CreateNetDriver);
    inline auto InitListen = (bool (*)(SDK::UNetDriver*, SDK::UWorld*, SDK::FURL&, bool, UC::FString)) (ImageBase + Addresses::InitListen);
    inline auto SetWorld = (void (*)(SDK::UNetDriver*, SDK::UWorld*)) (ImageBase + Addresses::SetWorld);
    inline auto ServerReplicateActors = (void (*)(SDK::UReplicationDriver*, float)) (ImageBase + Addresses::ServerReplicateActors);
    inline auto Realloc = (void* (*)(void*, __int64, unsigned int)) (ImageBase + Addresses::Realloc);
    inline auto StaticFindObject = (SDK::UObject * (*)(SDK::UClass*, SDK::UObject*, const wchar_t*, bool)) (ImageBase + Addresses::StaticFindObject);
    inline auto StaticLoadObject = (SDK::UObject * (*)(SDK::UClass*, SDK::UObject*, const wchar_t*, const wchar_t*, uint32_t, SDK::UObject*, bool)) (ImageBase + Addresses::StaticLoadObject);
};

static void Hook(uint64 Address, void* Detour, void** OG)
{
    MH_CreateHook(LPVOID(Address), Detour, OG);
    MH_EnableHook(LPVOID(Address));
}