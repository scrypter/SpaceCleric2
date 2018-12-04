// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LightManager.generated.h"

UCLASS()
class SPACECLERIC_API ALightManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightManager();

private:
	UPROPERTY(category="Sun", VisibleInstanceOnly)
	float SunAngle;

	UPROPERTY(category="Sun", EditAnywhere)
	class ADirectionalLight* Sun;

	UPROPERTY(category="Sun", EditAnywhere)
	class ASkySphere* SkyDome;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Update the lights based on time of day
	void Update(float Hour);

	
};
