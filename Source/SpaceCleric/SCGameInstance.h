// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SCGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPACECLERIC_API USCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USCGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(uint32 Index);

	UFUNCTION(Exec)
	void GetSessions();

private:
	bool bIsTraveling = false;
	bool bIsLan = true;
	bool bUseLobbies = true;
	bool bIsSearchable = true;
	bool bFriendsOnly = false;
	bool bLetPublicJoin = true;
	uint32 iNumPrivateConnections = 5;
	uint32 iNumPublicConnections = 5;
	uint32 iMaxSearchResults = 100;

	void OnConnectionStatusChangedDelegates(const FString& ServiceName, EOnlineServerConnectionStatus::Type LastConnectionState, EOnlineServerConnectionStatus::Type ConnectionState);

	IOnlineSessionPtr SessionInterface;

	void CreateSession(FName SessionName);
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionscomplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionCompleteDelegate(FName SessionName, bool bWasSuccessful);

	const FName DEFAULT_SESSION_NAME = TEXT("SpaceCleric Session");
	FName SessionName = DEFAULT_SESSION_NAME;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
