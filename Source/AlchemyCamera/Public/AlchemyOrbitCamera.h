//The MIT License(MIT)
//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

#pragma once

#include "GameFramework/Pawn.h"
#include "AlchemyOrbitCamera.generated.h"


/**
*
*/
UCLASS()
class ALCHEMYCAMERA_API AAlchemyOrbitCamera : public APawn
{
	GENERATED_BODY()

		//Side view camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* OrbitCameraComponent;

	//Camera boom positioning the camera beside the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Prop, meta = (AllowPrivateAccess = "true"))
	float FEaseMultiplier = 3.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Prop, meta = (AllowPrivateAccess = "true"))
	float FOrbitMultiplier = 0.15f;

protected:
	FVector FTouchDelta;
	FVector FPreviousLocation;
	FVector FDelayedLocation;

	bool bIsTouching;

	void Orbit(float Val);
	virtual void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);
	virtual void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);
	virtual void TouchRepeat(const ETouchIndex::Type FingerIndex, const FVector Location);

	virtual void MoveX(float Val);
	virtual void MoveY(float Val);
	virtual void MouseDown();
	virtual void MouseUp();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:


	AAlchemyOrbitCamera(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaSeconds) override;

	//Returns SideViewCameraComponent subobject
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return OrbitCameraComponent; }
	// Returns CameraBoom subobject
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

};
