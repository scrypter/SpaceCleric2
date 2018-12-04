// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"

UTimeManager::UTimeManager()
{
    // Set one day to day length in hours
    OneDay = DayLengthInMinutes * 60.0f;

    // The amount of real time in a game hour
    OneHour = OneDay / 24.0f;
}

UFUNCTION(Server, WithValidation, Reliable)
void UTimeManager::Tick(float DeltaTime)
{
    Hour += (DeltaTime / OneHour);
    if(Hour > 24.0f)
    {
        Hour -= 24.0f;
    }
}

void UTimeManager::SetDayLengthInMinutes(float DayLengthInMinutesParam)
{
    DayLengthInMinutes = DayLengthInMinutesParam;
}

float UTimeManager::GetDayLengthInMinutes()
{
    return DayLengthInMinutes;
}

float UTimeManager::GetHour()
{
    return Hour;
}