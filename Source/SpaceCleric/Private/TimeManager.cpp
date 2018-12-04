// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"
#include "LightManager.h"


// Sets default values
ATimeManager::ATimeManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeManager::BeginPlay()
{
	Super::BeginPlay();
	
	// Set one day to day length in hours
	OneDay = DayLengthInMinutes * 60;

	// The amount of real time in an hour
	OneHour = OneDay / 24.0;

}

// Called every frame
void ATimeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Hour += (DeltaTime / OneHour);
	if(Hour > 24.0f)
	{
		Hour -= 24.0f;
	}
	LightManager->Update(Hour);
}

void ATimeManager::SetDayLengthInMinutes(float DayLengthInMinutesParam)
{
	DayLengthInMinutes = DayLengthInMinutesParam;
}

void ATimeManager::SetHour(float HourParam)
{
	Hour = HourParam;
}

float ATimeManager::GetDayLengthInMinutes()
{
	return DayLengthInMinutes;
}

float ATimeManager::GetHour()
{
	return Hour;
}