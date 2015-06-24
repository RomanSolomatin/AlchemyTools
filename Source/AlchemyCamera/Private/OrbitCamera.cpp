//The MIT License(MIT)
//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

#include "AlchemyCamera.h"
#include "OrbitCamera.h"


AOrbitCamera::AOrbitCamera(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

	FOrbitMultiplier = 0.1f;
	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule
	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 15.0f;
	CameraBoom->RelativeRotation = FRotator(0.f, 180.f, 0.f);
	CameraBoom->bDoCollisionTest = false;
	RootComponent = CameraBoom;

	// Create a camera and attach to boom
	OrbitCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("OrbitViewCamera"));
	OrbitCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	OrbitCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

}

//////////////////////////////////////////////////////////////////////////
// Input

void AOrbitCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);
	InputComponent->BindAxis("MouseX", this, &AOrbitCamera::MoveX);
	InputComponent->BindAxis("MouseY", this, &AOrbitCamera::MoveY);
	InputComponent->BindTouch(IE_Pressed, this, &AOrbitCamera::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AOrbitCamera::TouchStopped);
	InputComponent->BindTouch(IE_Repeat, this, &AOrbitCamera::TouchRepeat);
	InputComponent->BindAction("Touch", IE_Pressed, this, &AOrbitCamera::MouseDown);
	InputComponent->BindAction("Touch", IE_Released, this, &AOrbitCamera::MouseUp);
}

void AOrbitCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//Rotate and ease the Actor based on the input delta
	FTouchDelta = FMath::VInterpTo(FTouchDelta, FVector(0.0f, 0.0f, 0.0f), DeltaSeconds, FEaseMultiplier);
	const FRotator YawRotation(0, FTouchDelta.X * FOrbitMultiplier, 0);
	AddActorWorldRotation(YawRotation);
	const FRotator PitchRotation(-FTouchDelta.Y * FOrbitMultiplier, 0, 0);
	AddActorLocalRotation(PitchRotation);
}

void AOrbitCamera::MouseDown()
{
	bIsTouching = true;
}

void AOrbitCamera::MouseUp()
{
	bIsTouching = false;
}

void AOrbitCamera::MoveX(float Val)
{
	if (!bIsTouching) return;

	if (bIsTouching && Controller != NULL) FTouchDelta.X = Val * 16.0f;
}

void AOrbitCamera::MoveY(float Val)
{
	if (bIsTouching && Controller != NULL) FTouchDelta.Y = -Val * 16.0f;
}

void AOrbitCamera::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FDelayedLocation = FPreviousLocation = Location;
}

void AOrbitCamera::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	
}

void AOrbitCamera::TouchRepeat(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FDelayedLocation = FPreviousLocation;
	FTouchDelta = Location - FDelayedLocation;
	FPreviousLocation = Location;
}