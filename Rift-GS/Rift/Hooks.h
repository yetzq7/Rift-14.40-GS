#pragma once

inline bool ReadyToStartMatch(AFortGameModeAthena* GameMode)
{
	static bool bFirstTouchingSession = false;
	auto GameState = (AFortGameStateAthena*)GameMode->GameState;
	if (!GameState || !GameState->MapInfo) return false; 
	if (!bFirstTouchingSession)
	{	
		static UFortPlaylistAthena* Playlist = UObject::FindObject<UFortPlaylistAthena>("FortPlaylistAthena Playlist_DefaultSolo.Playlist_DefaultSolo"); 
		GameState->CurrentPlaylistInfo.BasePlaylist = Playlist;
		GameState->CurrentPlaylistInfo.OverridePlaylist = Playlist;
		GameState->CurrentPlaylistInfo.PlaylistReplicationKey++;

		GameMode->CurrentPlaylistId = Playlist->PlaylistId;
		GameMode->CurrentPlaylistName = Playlist->PlaylistName;

		GameState->CurrentPlaylistId = Playlist->PlaylistId;

		GameState->AirCraftBehavior = Playlist->AirCraftBehavior;

		GameMode->WarmupRequiredPlayerCount = 1; 

		bFirstTouchingSession = true;
	}

	static bool bListen = false;
	if (!bListen)
	{
		FName GameNetDriver = UKismetStringLibrary::Conv_StringToName(L"GameNetDriver");
		UNetDriver* NetDriver = Funcs::CreateNetDriver(UEngine::GetEngine(), UWorld::GetWorld(), GameNetDriver);

		UWorld::GetWorld()->NetDriver = NetDriver;

		if (UWorld::GetWorld()->NetDriver)
		{
			UWorld::GetWorld()->NetDriver->NetDriverName = GameNetDriver;
			UWorld::GetWorld()->NetDriver->World = UWorld::GetWorld();

			FURL URL{}; 
			URL.Port = 7777;
			Funcs::InitListen(UWorld::GetWorld()->NetDriver, UWorld::GetWorld(), URL, false, {});

			Funcs::SetWorld(UWorld::GetWorld()->NetDriver, UWorld::GetWorld());

			for (int i = 0; i < UWorld::GetWorld()->LevelCollections.Num(); i++)

			{
				UWorld::GetWorld()->LevelCollections[1].NetDriver = UWorld::GetWorld()->NetDriver;
			}

			GameMode->bWorldIsReady = true;

			GameState->OnRep_CurrentPlaylistInfo();
			GameState->OnRep_CurrentPlaylistId();
		}

		bListen = true;
	}

	return GameMode->AlivePlayers.Num() > 0;
 }

inline APawn* SpawnDefaultPawnFor(AFortGameModeAthena* GameMode, AFortPlayerControllerAthena* PC, AActor* StartSpot)
{
	auto Transform = StartSpot->GetTransform();

	return GameMode->SpawnDefaultPawnAtTransform(PC, Transform);
}

static int ReturnTrue()
{
	return 1;
}

static void ReturnHook()
{
	return;
}

inline void (*TickFlush_OG)(UNetDriver* Driver, float DeltaSeconds);
inline void TickFlush(UNetDriver* Driver, float DeltaSeconds)
{ 
	if (Driver->ReplicationDriver)
	{
		Funcs::ServerReplicateActors(Driver->ReplicationDriver, DeltaSeconds);
	}

	return TickFlush_OG(Driver, DeltaSeconds);
}