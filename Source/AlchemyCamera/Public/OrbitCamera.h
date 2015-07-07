//The MIT License(MIT)
//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

#pragma once

#include "GameFramework/Pawn.h"
#include "OrbitCamera.generated.h"


/**
*
*/
UCLASS()
class ALCHEMYCAMERA_API AOrbitCamera : public APawn
{
	GENERATED_BODY()

		//Side view camera
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* OrbitCameraComponent;

	//Camera boom positioning the camera beside the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit", meta = (AllowPrivateAccess = "true"))
		float FOrbitEase = 3.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit", meta = (AllowPrivateAccess = "true"))
		float FOrbitMultiplier = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit", meta = (AllowPrivateAccess = "true"))
		bool bCanOrbit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orbit", meta = (AllowPrivateAccess = "true"))
		bool bCanPan;

	FVector FOrbitDelta;


public:

	AOrbitCamera(const FObjectInitializer& ObjectInitializer);

	/*
	Orbits the camera on the X axis according to the deltaX parameter
	deltaY requires screen space units
	*/
	UFUNCTION(BlueprintCallable, Category = "Orbit")
		virtual void OrbitX(float DeltaX);
	/*
	Orbits the camera on the Y axis according to the deltaY parameter
	DeltaY requires screen space units
	*/
	UFUNCTION(BlueprintCallable, Category = "Orbit")
		virtual void OrbitY(float DeltaY);

	UFUNCTION(BlueprintCallable, Category = "Pan")
		virtual void Pan(const float DeltaX, const float DeltaY);

	virtual void Tick(float DeltaSeconds) override;

	//Returns SideViewCameraComponent subobject
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return OrbitCameraComponent; }
	// Returns CameraBoom subobject
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
