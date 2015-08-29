//The MIT License(MIT)
//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

#include "AlchemyUtils.h"
#include "Perlin.h"
#include "ShakeComponent.h"

UShakeComponent::UShakeComponent()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UShakeComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	shake_x_val += DeltaTime;
	shake_y_val += DeltaTime;
	shake_z_val += DeltaTime;

	float xVal = shakeX ? UPerlin::Fractal1D(Octave_0, shake_x_val, frequency.X, amplitude.X, lacunarity.X, persistence.X) : 0.0f;
	float yVal = shakeY ? UPerlin::Fractal1D(Octave_1, shake_y_val, frequency.Y, amplitude.Y, lacunarity.Y, persistence.Y) : 0.0f;
	float zVal = shakeZ ? UPerlin::Fractal1D(Octive_2, shake_z_val, frequency.Z, amplitude.Z, lacunarity.Z, persistence.Z) : 0.0f;

	this->GetOwner()->AddActorLocalOffset(FVector(xVal - prev_x_val, yVal - prev_y_val, zVal- prev_z_val));

	prev_x_val = xVal;
	prev_y_val = yVal;
	prev_z_val = zVal;
}