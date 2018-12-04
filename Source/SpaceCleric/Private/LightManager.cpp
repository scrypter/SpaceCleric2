// Fill out your copyright notice in the Description page of Project Settings.


#include "LightManager.h"
#include "../Public/SkySphere.h"

#include "EngineUtils.h"
#include "Engine/DirectionalLight.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ULightManager::ULightManager()
{}

// Set the Sun and SkyDome to actors in the level if they exist
// Sun looks for an ADirectionalLight with name Sun
// SkyDome looks for an ASkySphere with name Sky
void ULightManager::BeginPlay()
{
    // Need to move this to something that occurs after OnBeginPlay
    // Scan for ADirectionalLight named "Sun"
    for (TActorIterator<ADirectionalLight> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        if(ActorItr->GetName() == "Sun")
        {
            Sun = *ActorItr;
        }
    }

    // If "Sun" not found, log it
    if(!IsValid(Sun))
    {
        UE_LOG(LogTemp, Warning, TEXT("LightManager could not find ADirectionalLight called Sun"));
    }


    // Scan for ASkySphere
    for (TActorIterator<ASkySphere> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        if(ActorItr->GetName() == "Sky")
        {
            SkyDome = *ActorItr;
        }
    }

    // If ASkySphere not found, log it
    if(!IsValid(SkyDome))
    {
        UE_LOG(LogTemp, Warning, TEXT("LightManager could not find ASkySphere called Sky"));
    }
}

// Update the sun values
UFUNCTION( Client, unreliable)
void ULightManager::UpdateSun(float Hour)
{
    SunAngle = Hour / 6.0f * 90.0f + 90.0f;
    if(IsValid(Sun) && IsValid(SkyDome))
    {
        Sun->SetActorRotation(UKismetMathLibrary::MakeRotator(0.0f, SunAngle, 0.0f));
	    SkyDome->UpdateSunDirection();
    }
}

// Update the lights based on time of day
void ULightManager::Update(float Hour)
{
    UpdateSun(Hour);
}