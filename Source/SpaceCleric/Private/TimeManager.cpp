// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"

float UTimeManager::GetHour()
{
    return Hour;
}

void UTimeManager::Update(float DeltaTime)
{
    Hour += DeltaTime / OneHourInRealSeconds;
    if(Hour > 24.0)
    {
        Hour -= 24.0;
    }
}

void UTimeManager::SetDayLengthInRealMinutes(float DayLengthParam)
{
    DayLengthInRealMinutes = DayLengthParam;
    OneGameDayInGameHours = DayLengthInRealMinutes * 60.0;
    OneHourInRealSeconds = OneGameDayInGameHours / 24.0;
}

