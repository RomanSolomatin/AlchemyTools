/**
* Perlin.h has been appropriated for Unreal from Chris Little's github at https://github.com/SRombauts/SimplexNoise through the MIT licence
* 
* Copyright Chris Little 2012
* Author: Chris Little
*/

#pragma once
#include "Object.h"
#include "Engine.h"
#include <cstddef>
#include <cstdint>
#include "Perlin.generated.h"

/**
 * 
 */
UCLASS()
class ALCHEMYUTILS_API UPerlin : public UObject
{
	GENERATED_BODY()
	
	public:
		// 1D Perlin simplex noise
		UFUNCTION(BlueprintCallable, category = "Utility")
		static float Noise1D(float x);
		// 2D Perlin simplex noise
		UFUNCTION(BlueprintCallable, category = "Utility")
		static float Noise2D(float x, float y);

		// Fractal/Fractional Brownian Motion (fBm) noise summation
		UFUNCTION(BlueprintCallable, Category = "Utility")
		static float Fractal1D(int32 octaves, float x, float frequency = 1.0f, float amplitude = 1.0f, float lacunarity = 2.0f, float persistence = 0.5f);
		UFUNCTION(BlueprintCallable, Category = "Utility")
		static float Fractal2D(int32 octaves, float x, float y, float frequency = 1.0f, float amplitude = 1.0f, float lacunarity = 2.0f, float persistence = 0.5f);
};
