// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Curves/CurveLinearColor.h"
#include "Engine/DirectionalLight.h"

#include "SkySphere.generated.h"

UCLASS()
class SPACECLERIC_API ASkySphere : public AActor
{
	GENERATED_BODY()

	/** COMPONENTS */
	// Static mesh for sky sphere
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* SkySphereMesh;

	// Base component
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SkySphereMeshParent;

	/** VARIABLES */
		// Material Interface
	UPROPERTY(EditAnywhere)
	class UMaterialInterface* ParentMaterial;

	// Material for Sky
	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* SkyMaterial;

	// Horizon color curve
	UPROPERTY(EditAnywhere)
	UCurveLinearColor* HorizonColorCurve;

	// Zenith color curve
	UPROPERTY(EditAnywhere)
	UCurveLinearColor* ZenithColorCurve;

	// Cloud color curve
	UPROPERTY(EditAnywhere)
	UCurveLinearColor* CloudColorCurve;
	
public:	
	// Sets default values for this actor's properties
	ASkySphere();

	// Should material refresh?
	UPROPERTY(EditAnywhere)
	bool ShouldRefreshMaterial = false;

	// Directional light representing rays from sun
	UPROPERTY(EditAnywhere)
	ADirectionalLight* DirectionalLightActor;

	// Should the colors be determined by sun position
	UPROPERTY(EditAnywhere)
	bool ColorsDeterminedBySunPosition = true;

	// How bright the sun is
	UPROPERTY(EditAnywhere)
	float SunBrightness = 50.0f;

	// How fast the clouds move
	UPROPERTY(EditAnywhere)
	float CloudSpeed = 1.0f;

	// How "soft" the clouds look
	UPROPERTY(EditAnywhere)
	float CloudOpacity = 0.7f;

	// How bright stars are
	UPROPERTY(EditAnywhere)
	float StarsBrightness = 0.1f;

	// Refresh the material
	UFUNCTION(BlueprintCallable)
	void RefreshMaterial();

	// Update the Sun's direction
	UFUNCTION(BlueprintCallable)
	void UpdateSunDirection();

private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
