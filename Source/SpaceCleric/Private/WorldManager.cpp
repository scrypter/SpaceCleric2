// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"


// Sets default values
AWorldManager::AWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWorldManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWorldManager::Init()
{
	LightManager = NewObject<ULightManager>();
	TimeManager = NewObject<UTimeManager>();
	TimeManager->SetDayLengthInRealMinutes(GameHourInRealMinutes);
	CalendarManager = NewObject<UCalendarManager>();
}

// Called every frame
void AWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
