// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightManager.h"

#include "TimeManager.generated.h"

UCLASS()
class SPACECLERIC_API ATimeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(category="Time", EditAnywhere)
	float Hour;

	UPROPERTY(category="Time", EditAnywhere)
	float DayLengthInMinutes;

	UPROPERTY(category="Time", EditAnywhere)
	ALightManager* LightManager;

	UPROPERTY(category="Time", VisibleInstanceOnly)
	float OneDay;

	UPROPERTY(category="Time", VisibleInstanceOnly)
	float OneHour;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** SETTERS */
	UFUNCTION(Category="Time", BlueprintCallable)
	void SetDayLengthInMinutes(float DayLengthInMinutesParam);

	UFUNCTION(Category="Time", BlueprintCallable)
	void SetHour(float HourParam);
	
	/** GETTERS */
	UFUNCTION(Category="Time", BlueprintCallable)
	float GetDayLengthInMinutes();

	UFUNCTION(Category="Time", BlueprintCallable)
	float GetHour();

	
	
};
