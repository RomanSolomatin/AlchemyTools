// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "SideScrollerMovementComponent.generated.h"

/** Movement modes for Characters.  */
UENUM(BlueprintType)
enum class ECustomMovementMode :uint8
{
	MOVE_Climbing		UMETA(DisplayName = "Climbing"),
};

/**
 * 
 */
UCLASS()
class ALCHEMYSIDESCROLLER_API USideScrollerMovementComponent : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()
//public:
	//UPROPERTY(Category = MovementMode, BlueprintReadOnly)
	//TEnumAsByte<enum ECustomMovementMode> NewCustomMovementMode;
	
public:
	virtual bool IsClimbing() const;

protected:
	
	//virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
};
