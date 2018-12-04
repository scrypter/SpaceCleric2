// Fill out your copyright notice in the Description page of Project Settings.


#include "SCGameInstance.h"

#include "GameFramework/PlayerController.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

USCGameInstance::USCGameInstance(const FObjectInitializer & ObjectInitializer)
{ }

void USCGameInstance::Init()
{
    bIsTraveling = false;
    IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
    if (SubSystem != nullptr)
    {
        SubSystem->OnConnectionStatusChangedDelegates.AddUObject(this, &USCGameInstance::OnConnectionStatusChanged);

        if (*SubSystem->GetSubsystemName().ToString() == FString("NULL"))
        {
            bIsLan = true;
        }
        else
        {
            bIsLan = false;
        }

		UE_LOG(LogTemp, Warning, TEXT("Using subsystem %s"),*SubSystem->GetSubsystemName().ToString());

        SessionInterface = SubSystem->GetSessionInterface();

        if (SessionInterface.IsValid())
        {
            SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &USCGameInstance::OnCreateSessionComplete);
            SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &USCGameInstance::OnDestroySessionComplete);
            SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &USCGameInstance::OnFindSessionscomplete);
            SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &USCGameInstance::OnJoinSessionComplete);
        }
    }
    else
    {
		UE_LOG(LogTemp, Warning, TEXT("Found no subsystem"));
    }
}

void USCGameInstance::Host()
{
    if (SessionInterface.IsValid())
    {
        FOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SessionName);
        if (ExistingSession != nullptr)
        {
            SessionInterface->DestroySession(SessionName);
        }
        else
        {
            CreateSession(SessionName);
        }
    }
}

void USCGameInstance::Join(uint32 Index)
{
    if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	SessionInterface->JoinSession(0, SessionName, SessionSearch->SearchResults[Index]);
}

void USCGameInstance::GetSessions()
{
    SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = bIsLan;
		SessionSearch->MaxSearchResults = iMaxSearchResults;
		if (bUseLobbies)
		{
			SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		}
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		UE_LOG(LogTemp, Warning, TEXT("Started search for sessions"));
	}
}

void USCGameInstance::OnConnectionStatusChanged(const FString & ServiceName, EOnlineServerConnectionStatus::Type LastConnectionState, EOnlineServerConnectionStatus::Type ConnectionState)
{
    // UE_LOG(LogTemp, Warning, TEXT("Service Name: %s"), *ServiceName);
	// UE_LOG(LogTemp, Warning, TEXT("Last Connection State: %s"), LastConnectionState);
	// UE_LOG(LogTemp, Warning, TEXT("Connection State: %s"), ConnectionState);
}

void USCGameInstance::CreateSession(FName fnSessionName)
{
    FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = bIsLan;
	SessionSettings.NumPublicConnections = iNumPublicConnections;
	SessionSettings.NumPrivateConnections = iNumPrivateConnections;
	SessionSettings.bShouldAdvertise = bIsSearchable;
	SessionSettings.bUsesPresence = bUseLobbies;
	SessionSettings.bAllowJoinViaPresenceFriendsOnly = (bUseLobbies && bFriendsOnly);
	SessionSettings.bAllowJoinViaPresence = (bUseLobbies && bLetPublicJoin);

	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bAllowInvites = true;

	SessionInterface->CreateSession(0, SessionName, SessionSettings);
	UE_LOG(LogTemp, Warning, TEXT("Making request to create session"));
}

void USCGameInstance::OnCreateSessionComplete(FName fnSessionName, bool bWasSuccessful)
{
    if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finished creating session"));
		
		UEngine* Engine = GetEngine();
		if (!ensure(Engine != nullptr)) return;

		
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		bIsTraveling = true;
		World->ServerTravel("/Game/Maps/Main?listen");
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to create session "));
	}
}

void USCGameInstance::OnFindSessionscomplete(bool bWasSuccessful)
{
    UE_LOG(LogTemp, Warning, TEXT("Finished search for sessions"));
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Warning, TEXT("Successfully searched for sessions"));
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;

		
		for (FOnlineSessionSearchResult& SearchResult : SearchResults)
		{
			if (SearchResult.IsValid()) {
				UE_LOG(LogTemp, Warning, TEXT("Found session named: %s"), *SearchResult.GetSessionIdStr());
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Something went wrong while searching for sessions"));
	}
}

void USCGameInstance::OnJoinSessionComplete(FName fnSessionName, EOnJoinSessionCompleteResult::Type Result)
{
    if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;


	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect string."))
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void USCGameInstance::OnDestroySessionComplete(FName fnSessionName, bool bWasSuccessful)
{
    if (bWasSuccessful) {
		UE_LOG(LogTemp, Warning, TEXT("Successfully destroyed session"));
		Host();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session"));
	}
}


