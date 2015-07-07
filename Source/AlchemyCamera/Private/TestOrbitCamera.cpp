//The MIT License(MIT)
//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

#include "AlchemyCamera.h"
#include "Engine.h"
#include "TestOrbitCamera.h"

ATestOrbitCamera::ATestOrbitCamera(const FObjectInitializer& ObjectInitializer)
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
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 0.0f);
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

void ATestOrbitCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//Rotate and ease the Actor based on the input delta
	
	if (FOrbitDelta.Size() <= 0) return;
	const FRotator YawRotation(0, FOrbitDelta.X, 0);
	AddActorWorldRotation(YawRotation);
	const FRotator PitchRotation(-FOrbitDelta.Y, 0, 0);
	AddActorLocalRotation(PitchRotation);
	FOrbitDelta = FMath::VInterpTo(FOrbitDelta, FVector(0.0f, 0.0f, 0.0f), DeltaSeconds, FOrbitEase);
	UE_LOG(LogTemp, Warning, TEXT("OrbitDeltaX: %f"), FOrbitDelta.X);
}

void ATestOrbitCamera::OrbitX(float DeltaX)
{
	if (bCanOrbit && Controller != NULL) FOrbitDelta.X = DeltaX * FOrbitMultiplier;
}

void ATestOrbitCamera::OrbitY(float DeltaY)
{
	if (bCanOrbit && Controller != NULL) FOrbitDelta.Y = -DeltaY * FOrbitMultiplier;
}

void ATestOrbitCamera::Pan(const float DeltaX, const float DeltaY)
{
	if (!bCanPan || Controller == NULL) return;
	
	UPlayer* player = GetNetOwningPlayer();
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(player);

	if (LocalPlayer != NULL && LocalPlayer->ViewportClient != NULL && LocalPlayer->ViewportClient->Viewport != NULL)
	{
		/*
		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
			LocalPlayer->ViewportClient->Viewport,
			GetWorld()->Scene,
			LocalPlayer->ViewportClient->EngineShowFlags).SetRealtimeUpdate(true));

		FVector ViewLocation;
		FRotator ViewRotation;
		FSceneView* SceneView = LocalPlayer->CalcSceneView(
			&ViewFamily,
			ViewLocation,
			ViewRotation,
			LocalPlayer->ViewportClient->Viewport);

		FVector WorldOrigin;
		FVector WorldDirection;
		
		//Controller->CastToPlayerController()->GetMousePosition(MouseX, MouseY);
		//UE_LOG(LogTemp, Warning, TEXT("MouseX: %f | Val: %f"), MouseX, DeltaX);

		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		//UE_LOG(LogTemp, Warning, TEXT("width: %f | height: %f"), ViewportSize.X, ViewportSize.Y);
		//UE_LOG(LogTemp, Warning, TEXT("deltaX: %f | deltaY: %f"), DeltaX, DeltaY);

		SceneView->DeprojectFVector2D(FVector2D(ViewportSize.X/2 - DeltaX, ViewportSize.Y/2 - DeltaY), WorldOrigin, WorldDirection);
		FVector SpringOffset = WorldOrigin + (WorldDirection * CameraBoom->TargetArmLength);

		CameraBoom->SetWorldLocation(SpringOffset);

		//CameraBoom->SetWorldLocation(SpringOffset);
		//CameraBoom->AddLocalOffset()
		//FVector SpringOffset = WorldOrigin + (WorldDirection * CameraBoom->TargetArmLength) CameraBoom->AddLocalTransform()	
		//UE_LOG(LogTemp, Warning, TEXT("XOffset: %f"), SpringOffset.X);
		DrawDebugSphere(GetWorld(), SpringOffset, 3.0f, 10, FColor::Blue, true, 100.0f);
		//UE_LOG(LogTemp, Warning, TEXT("X: %f Y: %f Z: %f"), WorldOrigin.X, WorldOrigin.Y, WorldOrigin.Z);
		*/
	}
}