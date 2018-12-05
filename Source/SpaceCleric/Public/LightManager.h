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

	UFUNCTION(BlueprintCallable)
	void Update(float HourParam);

	UPROPERTY(Category="Sun", EditAnywhere)
	class ADirectionalLight* Sun;

protected:
	UPROPERTY(Category="Sun", VisibleAnywhere, BlueprintReadOnly)
	float SunAngle;

public:
	UFUNCTION(Category="Sun", BlueprintCallable)
	void SetSun(ADirectionalLight* SunParam);

	UFUNCTION(Category="Sun", BlueprintCallable)
	ADirectionalLight* GetSun();
	
};