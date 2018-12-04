// Fill out your copyright notice in the Description page of Project Settings.


#include "LightManager.h"
#include "Engine/DirectionalLight.h"
#include "../Public/SkySphere.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values
ALightManager::ALightManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALightManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Update the lights based on time of day
void ALightManager::Update(float Hour)
{
	SunAngle = Hour / 6.0f * 90.0f + 90.0f;
	
	Sun->SetActorRotation(UKismetMathLibrary::MakeRotator(0.0f, SunAngle, 0.0f));

	SkyDome->UpdateSunDirection();
}