// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"
#include "../Public/TimeManager.h"
#include "../Public/LightManager.h"


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
	TimeManager = NewObject<UTimeManager>();
	LightManager = NewObject<ULightManager>();
}

void AWorldManager::Tick(float DeltaTime)
{
	TimeManager->Tick(DeltaTime);
	LightManager->Update(TimeManager->GetHour());
}

