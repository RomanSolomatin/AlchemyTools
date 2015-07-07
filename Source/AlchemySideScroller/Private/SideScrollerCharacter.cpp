// Fill out your copyright notice in the Description page of Project Settings.

#include "AlchemySideScroller.h"
#include "SideScrollerMovementComponent.h"
#include "SideScrollerCharacter.h"

#define COLLISION_INTERACTIVE ECC_GameTraceChannel1

// Sets default values
ASideScrollerCharacter::ASideScrollerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USideScrollerMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 40.f);
	CameraBoom->RelativeRotation = FRotator(0.f, 270.0f, 0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1080.0f, 0.0f); // ...at this rotation rate
	//GetCharacterMovement()->WalkableFloorAngle = 45;
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASideScrollerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ASideScrollerCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ASideScrollerCharacter::StopJumping);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &ASideScrollerCharacter::CrouchAction);
	InputComponent->BindAction("Crouch", IE_Released, this, &ASideScrollerCharacter::UnCrouchAction);
	InputComponent->BindAxis("MoveRight", this, &ASideScrollerCharacter::MoveRight);
	InputComponent->BindAxis("MoveUp", this, &ASideScrollerCharacter::MoveUp);
	InputComponent->BindTouch(IE_Pressed, this, &ASideScrollerCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ASideScrollerCharacter::TouchStopped);
}

void ASideScrollerCharacter::CrouchAction()
{
	if (bCanClimb || bIsClimbing)
		return;
	Crouch();
}

void ASideScrollerCharacter::UnCrouchAction()
{
	if (bCanClimb || bIsClimbing)
		return;
	UnCrouch();
}

void ASideScrollerCharacter::MoveRight(float Value)
{
	//GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	HorizontalValue = Value;
	
	if (bIsClimbing || Value == 0)
		return;

	/*if (bIsClimbing)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Falling);
		bIsClimbing = false;
	}*/

	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void ASideScrollerCharacter::MoveUp(float Value)
{
	if (bCanClimb && Value!= 0)
	{
		if (!bIsClimbing)
		{
			bIsClimbing = true;
		}

		GetCharacterMovement()->Velocity = FVector(0, 0, 0);
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		RootComponent->AddLocalOffset(FVector(0, 0, ClimbMultiplier * Value));
		//AddMovementInput(FVector(0.0f, 0.0f, climbingMult), Value);
	}
}

void ASideScrollerCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	Jump();	
}

bool ASideScrollerCharacter::CanJumpInternal_Implementation() const
{
	const bool bCanHoldToJumpHigher = (GetJumpMaxHoldTime() > 0.0f) && IsJumpProvidingForce();
	//return true;
	
	const bool canJump = !bIsCrouched && CharacterMovement && (CharacterMovement->IsMovingOnGround() || bCanHoldToJumpHigher || bIsClimbing) && CharacterMovement->IsJumpAllowed() && !CharacterMovement->bWantsToCrouch;
	UE_LOG(LogTemp, Warning, TEXT("CanJump: %s"), canJump?TEXT("TRUE"):TEXT("FALSE"));
	return canJump;
}

void ASideScrollerCharacter::Jump()
{
	//GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	bIsClimbing = false;
	Super::Jump();
}

void ASideScrollerCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ASideScrollerCharacter::Interact()
{
	FHitResult Hit(ForceInit);
	
	const FVector start_trace = this->GetTransform().GetLocation();;
	const FVector direction = this->GetActorForwardVector();
	const FVector end_trace = start_trace + (direction * fInteractDist);
	
	const FName traceTag("RaycastTrace");
	GetWorld()->DebugDrawTraceTag = traceTag;

	FCollisionQueryParams TraceParams(FName(TEXT("")), true, this);

	TraceParams.TraceTag = traceTag;
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.bTraceComplex = true;

	if(GetWorld()->LineTraceSingle(Hit, start_trace, end_trace, COLLISION_INTERACTIVE, TraceParams))
		OnInteractionEvent.Broadcast(Hit);
}