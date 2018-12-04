// Fill out your copyright notice in the Description page of Project Settings.


#include "SkySphere.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/LightComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
ASkySphere::ASkySphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("Material'/Engine/EngineSky/M_Sky_Panning_Clouds2'"));

	if(MaterialAsset.Object)
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded M_Sky_Panning_Clouds2"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to load M_Sky_Panning_Clouds2"));
	}

	SkySphereMeshParent = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	
	SkySphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkySphereMesh"));
	SkySphereMesh->SetupAttachment(SkySphereMeshParent);

	SkyMaterial = SkySphereMesh->CreateDynamicMaterialInstance(0,
		MaterialAsset.Object);
}

// Called when the game starts or when spawned
void ASkySphere::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkySphere::UpdateSunDirection()
{
	float SunHeight = 0.0f;
	
	FLinearColor SunColor;
	FLinearColor LightDirection;
	
	FLinearColor HorizonColor = FLinearColor(FVector4(1.979559f, 2.586644f, 3.0f, 1.0f));
	FLinearColor ZenithColor = FLinearColor(FVector4(0.034046f, 0.109247f, 0.295f, 1.0f));
	FLinearColor CloudColor = FLinearColor(FVector4(0.855778f, 0.91902f, 1.0f, 1.0f));
	float HorizonFalloff = 3.0;

	// Set the direction of the light based on directional light actor
	FRotator ActorRotation = DirectionalLightActor->GetActorRotation();
	FVector RotationXVector = UKismetMathLibrary::Conv_RotatorToVector(ActorRotation);
	LightDirection = UKismetMathLibrary::Conv_VectorToLinearColor(RotationXVector);

	// // Set the color of the sun
	SunColor = DirectionalLightActor->GetLightComponent()->GetLightColor();		

	// Store the sun's height
	float Roll, Pitch, Yaw;
	UKismetMathLibrary::BreakRotator(ActorRotation, Roll, Pitch, Yaw);
	SunHeight = UKismetMathLibrary::MapRangeUnclamped(Pitch, 0, -90, 0, 1);
	
	
	HorizonColor = HorizonColorCurve->GetClampedLinearColorValue(SunHeight);
	ZenithColor = ZenithColorCurve->GetClampedLinearColorValue(SunHeight);
	CloudColor = CloudColorCurve->GetClampedLinearColorValue(SunHeight);
	HorizonFalloff = UKismetMathLibrary::Lerp(3.0f, 7.0f, UKismetMathLibrary::Abs(SunHeight));

	float StarBlending = UKismetMathLibrary::SelectFloat(UKismetMathLibrary::Abs(SunHeight), 0.0f, SunHeight < 0.0f);
	
	if (IsValid(SkyMaterial))
	{
		SkyMaterial->SetVectorParameterValue("Light direction", LightDirection);
		SkyMaterial->SetVectorParameterValue("Sun color", SunColor);
		SkyMaterial->SetVectorParameterValue("Horizon color", HorizonColor);
		SkyMaterial->SetVectorParameterValue("Zenith color", ZenithColor);
		SkyMaterial->SetVectorParameterValue("Cloud color", CloudColor);
		SkyMaterial->SetScalarParameterValue("Horizon falloff", HorizonFalloff);
		SkyMaterial->SetScalarParameterValue("Sun height", StarBlending);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("SkyMaterial is not valid"));
	}
}

void ASkySphere::RefreshMaterial()
{
	float SunHeight = 0.0f;
	
	FLinearColor SunColor;
	FLinearColor LightDirection;
	
	FLinearColor HorizonColor = FLinearColor(FVector4(1.979559f, 2.586644f, 3.0f, 1.0f));
	FLinearColor ZenithColor = FLinearColor(FVector4(0.034046f, 0.109247f, 0.295f, 1.0f));
	FLinearColor OverallColor = FLinearColor(FVector4(1.0f, 1.0f, 1.0f, 1.0f));
	FLinearColor CloudColor = FLinearColor(FVector4(0.855778f, 0.91902f, 1.0f, 1.0f));
	float HorizonFalloff = 3.0;

	// Set the Direction and color in SkyMaterial
	if (IsValid(DirectionalLightActor))
	{
		// Set the direction of the light based on directional light actor
		FRotator ActorRotation = DirectionalLightActor->GetActorRotation();
		FVector RotationXVector = UKismetMathLibrary::Conv_RotatorToVector(ActorRotation);
		LightDirection = UKismetMathLibrary::Conv_VectorToLinearColor(RotationXVector);

		// Set the color of the sun
		SunColor = DirectionalLightActor->GetLightComponent()->GetLightColor();		

		// Store the sun's height
		float Roll, Pitch, Yaw;
		UKismetMathLibrary::BreakRotator(ActorRotation, Roll, Pitch, Yaw);
		SunHeight = UKismetMathLibrary::MapRangeUnclamped(Pitch, 0, -90, 0, 1);
	} else 
	{
		// Set the direction of the light based on actor rotation
		float ClampedSunHeight = UKismetMathLibrary::MapRangeUnclamped(SunHeight, -1.0f, 1.0f, 90.0f, -90.0f);
		float Roll, Pitch, Yaw;
		FRotator ActorRotation = GetActorRotation();
		UKismetMathLibrary::BreakRotator(ActorRotation, Roll, Pitch, Yaw);
		FRotator ActorBasedRotator = UKismetMathLibrary::MakeRotator(0.0f, ClampedSunHeight, Yaw);
		FVector RotationXVector = UKismetMathLibrary::Conv_RotatorToVector(ActorBasedRotator);
		LightDirection = UKismetMathLibrary::Conv_VectorToLinearColor(RotationXVector);

		// Set the color of the sun via a lerp
		float LerpAlpha = UKismetMathLibrary::Clamp(SunHeight + 0.2f, 0.0f, 1.0f);
		FLinearColor LerpFrom = FLinearColor(FVector4(1.0f, 0.221f, 0.04f, 1.0f));
		FLinearColor LerpTo = FLinearColor(FVector4(0.954f, 0.901f, 0.74412f, 1.0f));
		SunColor = UKismetMathLibrary::LinearColorLerp(LerpFrom, LerpTo, LerpAlpha);
	}

	
	SkyMaterial->SetVectorParameterValue("Light direction", LightDirection);
	SkyMaterial->SetVectorParameterValue("Sun color", SunColor);

	// Set Horizon color, Zenith color, Cloud color, and Horizon falloff on sun position if it exists
	if (ColorsDeterminedBySunPosition)
	{
		HorizonColor = HorizonColorCurve->GetClampedLinearColorValue(SunHeight);
		ZenithColor = ZenithColorCurve->GetClampedLinearColorValue(SunHeight);
		CloudColor = CloudColorCurve->GetClampedLinearColorValue(SunHeight);
		HorizonFalloff = UKismetMathLibrary::Lerp(3.0f, 7.0f, UKismetMathLibrary::Abs(SunHeight));
	}

	SkyMaterial->SetVectorParameterValue("Horizon color", HorizonColor);
	SkyMaterial->SetVectorParameterValue("Zenith color", ZenithColor);
	SkyMaterial->SetVectorParameterValue("Overall color", OverallColor);
	SkyMaterial->SetVectorParameterValue("Cloud color", CloudColor);
	SkyMaterial->SetScalarParameterValue("Horizon falloff", HorizonFalloff);

	// Set Cloud speed, Sun brightness, Sun height, Cloud opacity, and Stars brightness
	SkyMaterial->SetScalarParameterValue("Cloud speed", CloudSpeed);
	SkyMaterial->SetScalarParameterValue("Sun brightness", SunBrightness);
	SkyMaterial->SetScalarParameterValue("Cloud opacity", CloudOpacity);
	SkyMaterial->SetScalarParameterValue("Stars brightness", StarsBrightness);

	// If sun height is negative, this value is used to blend in stars
	float StarBlending = UKismetMathLibrary::SelectFloat(UKismetMathLibrary::Abs(SunHeight), 0.0f, SunHeight < 0.0f);
	SkyMaterial->SetScalarParameterValue("Sun height", StarBlending);

}
