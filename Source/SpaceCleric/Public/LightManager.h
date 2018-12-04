// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LightManager.generated.h"

/**
 * 
 */
UCLASS()
class SPACECLERIC_API ULightManager : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this object's properties
	ULightManager();

	// When the 
	UFUNCTION(category="Event", BlueprintCallable)
	void BeginPlay();

private:
	UPROPERTY(category="Sun", VisibleAnywhere)
	float SunAngle;

	UPROPERTY(category="Sun", VisibleAnywhere)
	class ADirectionalLight* Sun;

	UPROPERTY(category="Sun", VisibleAnywhere)
	class ASkySphere* SkyDome;

	void UpdateSun(float Hour);

public:
	// Update the lights based on time of day
	void Update(float Hour);	
};
