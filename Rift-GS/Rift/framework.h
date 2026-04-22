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
#include "MinHook.h" // use "MinHook.h" instead of <MinHook.h> to avoid issues with include directories 
// #include "SDK/UnrealContainers.hpp" maybe remove
// #include "SDK/SDK/Basic.hpp" maybe remove

inline uint64 ImageBase = uint64(GetModuleHandle(0)); // maybe use InSDKUtils::GetImageBase(); idk *note*

namespace Addresses {
    inline uint64_t Step = 0x3757230;
    inline uint64_t StepExplicitProperty = 0x3757260;
    inline uint64_t CreateNetDriver = 0x50a7d60;
    inline uint64_t InitListen = 0xc51ec0;
    inline uint64_t SetWorld = 0x4e167a0;
    inline uint64_t GetNetMode = 0x510f080;
    inline uint64_t TickFlush = 0x4e17cc0;
    inline uint64_t ServerReplicateActors = 0x17022b0;
    inline uint64_t GetMaxTickRate = 0x50aebd0;
    inline uint64_t DispatchRequest = 0x14236d0;
    inline uint64_t Realloc = 0x3454080;
    inline uint64_t StaticFindObject = 0x37557d0;
    inline uint64_t StaticLoadObject = 0x3756cc0;
    inline uint64_t GIsClient = 0x91b549c;
    inline uint64_t GameSessionPatch = 0x20cff35;
    inline uint64_t EncryptionPatch = 0x51116ee;
    inline std::vector<uint64_t> NullFuncs = { 0x265cf20, 0x4cb6b80 };
    inline std::vector<uint64_t> RetTrueFuncs = {  };
};

namespace Funcs {
    inline auto CreateNetDriver = (SDK::UNetDriver * (*)(SDK::UEngine*, SDK::UWorld*, SDK::FName)) (ImageBase + Addresses::CreateNetDriver);
    inline auto InitListen = (bool (*)(SDK::UNetDriver*, SDK::UWorld*, SDK::FURL&, bool, UC::FString&)) (ImageBase + Addresses::InitListen);
    inline auto SetWorld = (void (*)(SDK::UNetDriver*, SDK::UWorld*)) (ImageBase + Addresses::SetWorld);
    inline auto ServerReplicateActors = (void (*)(SDK::UReplicationDriver*, float)) (ImageBase + Addresses::ServerReplicateActors);
    inline auto Realloc = (void* (*)(void*, __int64, unsigned int)) (ImageBase + Addresses::Realloc);
    inline auto StaticFindObject = (SDK::UObject * (*)(SDK::UClass*, SDK::UObject*, const wchar_t*, bool)) (ImageBase + Addresses::StaticFindObject);
    inline auto StaticLoadObject = (SDK::UObject * (*)(SDK::UClass*, SDK::UObject*, const wchar_t*, const wchar_t*, uint32_t, SDK::UObject*, bool)) (ImageBase + Addresses::StaticLoadObject);
};

static void Hook(uint64 Address, void* Detour, void** OG)
{
    MM_CreateHook(LPVoid(Address), Detour, OG);
    MM_EnableHook(LPVoid(Address));
}