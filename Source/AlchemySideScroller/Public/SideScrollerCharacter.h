// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "SideScrollerCharacter.generated.h"

UCLASS(config = Game)
class ALCHEMYSIDESCROLLER_API ASideScrollerCharacter : public ACharacter
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractionEvent, FHitResult, OtherComponent);
	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	uint32 bCanClimb : 1;

	/** Called for side to side input */
	void MoveRight(float Value);

	void MoveUp(float Value);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	virtual bool CanJumpInternal_Implementation() const override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual	void  Interact();

	

public:
	ASideScrollerCharacter(const FObjectInitializer& ObjectInitializer);

	//UPROPERTY(BlueprintReadOnly, replicatedUsing = OnRep_IsCrouched, Category = Character)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	uint32 bIsClimbing : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAcces = "true"))
	float fInteractDist = 10.0f;

	UPROPERTY(BlueprintAssignable, Category = "ButtonActivity")
	FInteractionEvent OnInteractionEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	float ClimbMultiplier;

	float HorizontalValue = 0.0f;

	virtual void Jump() override;

	void CrouchAction();
	void UnCrouchAction();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};