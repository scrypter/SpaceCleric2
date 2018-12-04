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
	
public:
	// Sets default values for this object's propertiese
	UTimeManager();

private:
	UPROPERTY(category="Time", VisibleAnywhere)
	float Hour;

	UPROPERTY(category="Time", EditAnywhere)
	float DayLengthInMinutes;

	UPROPERTY(category="Time", VisibleInstanceOnly)
	float OneDay;

	UPROPERTY(category="Time", VisibleInstanceOnly)
	float OneHour;

public:
	// Update the game time
	void Tick(float DeltaTime);

	/** SETTERS */
	UFUNCTION(Category="Time", BlueprintCallable)
	void SetDayLengthInMinutes(float DayLengthInMinutesParam);
	
	/** GETTERS */
	UFUNCTION(Category="Time", BlueprintCallable)
	float GetDayLengthInMinutes();

	UFUNCTION(Category="Time", BlueprintCallable)
	float GetHour();
};
