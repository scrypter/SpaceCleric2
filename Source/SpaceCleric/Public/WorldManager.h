// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CalendarManager.h"
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

	UPROPERTY(Category="Calendar", EditAnywhere, BlueprintReadWrite)
	UCalendarManager* CalendarManager;

	UPROPERTY(Category="Time", EditAnywhere, BlueprintReadWrite)
	UTimeManager* TimeManager;

	UPROPERTY(Category="LightManager", EditAnywhere, BlueprintReadWrite)
	ULightManager* LightManager;

	UPROPERTY(Category="LightManager", EditAnywhere, BlueprintReadWrite)
	float GameHourInRealMinutes = 30.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Category="WorldManager", BlueprintCallable)
	void Init();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
