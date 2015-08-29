//The MIT License(MIT)
//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

#pragma once
#include "Components/ActorComponent.h"
#include "Engine.h"
#include "ShakeComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALCHEMYUTILS_API UShakeComponent : public UActorComponent
{
	GENERATED_BODY()
		
public:	
	// Sets default values for this component's properties
	UShakeComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Value", meta = (AllowPrivateAccess = "true"))
		bool shakeX = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Value", meta = (AllowPrivateAccess = "true"))
		bool shakeY = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Value", meta = (AllowPrivateAccess = "true"))
		bool shakeZ = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Value", meta = (AllowPrivateAccess = "true"))
		int32 Octave_0 = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Value", meta = (AllowPrivateAccess = "true"))
		int32 Octave_1 = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Value", meta = (AllowPrivateAccess = "true"))
		int32 Octive_2 = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Value", meta = (AllowPrivateAccess = "true"))
		FVector frequency = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Value", meta = (AllowPrivateAccess = "true"))
		FVector amplitude = FVector(1.0f, 1.0f, 1.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Value", meta = (AllowPrivateAccess = "true"))
		FVector lacunarity = FVector(2.0f, 2.0f, 2.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Value", meta = (AllowPrivateAccess = "true"))
		FVector persistence = FVector(0.5f, 0.5f, 0.5f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Value", meta = (AllowPrivateAccess = "true"))
		float shake_x_val = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Value", meta = (AllowPrivateAccess = "true"))
		float shake_y_val = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shake Value", meta = (AllowPrivateAccess = "true"))
		float shake_z_val = 0.0f;
	
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	private:
		float prev_x_val = 0.0f;
		float prev_y_val = 0.0f;
		float prev_z_val = 0.0f;
};
