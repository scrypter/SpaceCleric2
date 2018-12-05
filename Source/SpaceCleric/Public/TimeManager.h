// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimeManager.generated.h"

/**
 * 
 */
UCLASS()
class SPACECLERIC_API UTimeManager : public UObject
{
	GENERATED_BODY()
	
	UPROPERTY(Category="Time", VisibleAnywhere)
	float Hour;

	UPROPERTY(Category="Time", EditAnywhere)
	float DayLengthInRealMinutes;

private:
	float OneGameDayInGameHours;
	float OneHourInRealSeconds;	

public:
	UFUNCTION(Category="Time", BlueprintCallable)
	float GetHour();

	UFUNCTION(Category="Time", BlueprintCallable)
	void Update(float DeltaTime);

	UFUNCTION(Category="Time", BlueprintCallable)
	void SetDayLengthInRealMinutes(float DayLengthParam);
};
