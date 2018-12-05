// Fill out your copyright notice in the Description page of Project Settings.

#include "LightManager.h"

#include "Kismet/KismetMathLibrary.h"
#include "Engine/DirectionalLight.h"


void ULightManager::Update(float HourParam)
{
    SunAngle = HourParam / 6.0 * 90.0 + 90.0;
    FRotator SunRotator = UKismetMathLibrary::MakeRotator(0.0, SunAngle, 0.0);
    Sun->SetActorRotation(SunRotator);
}

void ULightManager::SetSun(ADirectionalLight* SunParam)
{
    Sun = SunParam;
}

ADirectionalLight* ULightManager::GetSun()
{
    return Sun;
}