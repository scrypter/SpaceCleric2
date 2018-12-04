// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TimeManager.h"
#include "LightManager.h"
#include "WorldManager.generated.h"

UCLASS()
class SPACECLERIC_API AWorldManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldManager();

	UTimeManager* TimeManager;
	ULightManager* LightManager;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
};
