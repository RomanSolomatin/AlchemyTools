//The MIT License(MIT)
//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

#include "AlchemySideScroller.h"
#include "LadderTool.h"

ALadderTool::ALadderTool()
{
	//Create an "empty" object as the root
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootSceneComponent;
	//Create a trigger for other objects to interact with the ladder
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	BoxTrigger->InitBoxExtent(FVector(20, 20, 20));
	BoxTrigger->RegisterComponent();
	BoxTrigger->bWantsInitializeComponent = true;
	BoxTrigger->AttachTo(RootComponent);
	BoxTrigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	//Create a collider so objects can't pass throught the ladder
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->InitBoxExtent(FVector(20, 20, 20));
	BoxCollider->RegisterComponent();
	BoxCollider->bWantsInitializeComponent = true;
	BoxCollider->AttachTo(RootComponent);
	BoxCollider->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	//Give a visual clue as to the direction the ladder will be facing
	LadderFrontDirection = CreateDefaultSubobject<UArrowComponent>("Ladder Front Direction");
	LadderFrontDirection->AttachTo(RootComponent);
	LadderFrontDirection->SetLockedAxis(EDOFMode::YZPlane);
	//Draw a handle for the author to grab, position, and create the ladder height
	LadderUpHandle = CreateDefaultSubobject<UArrowComponent>("Ladder Up Handle");
	LadderUpHandle->AttachTo(RootComponent);
	LadderUpHandle->ArrowColor = FColor(0, 0, 128);
	LadderUpHandle->SetRelativeRotation(FRotator(90, 0, 0));
	LadderUpHandle->SetLockedAxis(EDOFMode::XYPlane);
	LadderUpHandle->bSelectable = true;
}
/*
*Called everytime a variable is changed
*Specifically we're looking to see if any ladder variables have been changed
*/
void ALadderTool::OnConstruction(const FTransform& Transform)
{
	//Destroy ladder parts and empty the ladder stack to begin rebuilding
	TArray<UStaticMesh*> meshStack;
	int i = 0;
	for (i = LadderComponentArray.Num() - 1; i > 0; --i)
	{
		if (LadderComponentArray[i] != NULL)
			LadderComponentArray[i]->UnregisterComponent();
		if (LadderComponentArray[i] != NULL)
			LadderComponentArray[i]->Deactivate();
		if (LadderComponentArray[i] != NULL)
			LadderComponentArray[i]->DetachFromParent();
		if (LadderComponentArray[i] != NULL)
			LadderComponentArray[i]->DestroyComponent();
	}

	LadderComponentArray.Empty();

	//Create a variable to store the position of the ladder pieces as they are build out
	FVector Pos = FVector(0, 0, 0);
	Pos = LadderUpHandle->GetRelativeTransform().TransformPosition(Pos);
	float handleZ = Pos.Z;
	float currentZ = 0;
	
	auto willAddMesh = [](UStaticMesh* mesh, float& currentZ, float handleZ)
	{
		float combinedZ = mesh->GetBounds().GetBox().GetSize().Z + currentZ;
		if (handleZ >= combinedZ)
		{
			currentZ = combinedZ;
			return true;
		}
		return false;
	};
	//First check and see if one bottom element can be added
	if (LadderBottom != NULL)
		if (willAddMesh(LadderBottom, currentZ, handleZ))
			meshStack.Add(LadderBottom);
	//Check and see if a top element can be added
	if (LadderTop != NULL)
		if (willAddMesh(LadderTop, currentZ, handleZ))
			meshStack.Add(LadderTop);
	//Insert as many rungs as the author has made room for with the handle
	if (LadderRungs != NULL && meshStack.Num() > 1)
		while (willAddMesh(LadderRungs, currentZ, handleZ))
			meshStack.Insert(LadderRungs, 1);
	
	currentZ = 0;
	for (i = 0; i < meshStack.Num(); i++)
	{
		FString name = meshStack[i]->GetName() + FString::FromInt(i);
		UStaticMeshComponent* meshComp = GenLadderComponent(meshStack[i], currentZ, FName(*name));
		LadderComponentArray.Add(meshComp);
		currentZ = meshStack[i]->GetBounds().GetBox().GetSize().Z + currentZ;
	}
	//Adjust the z scale of the Collider and Trigger to match the size of the ladder pieces
	BoxCollider->SetRelativeLocation(FVector(10, 0, currentZ / 2));
	BoxCollider->SetBoxExtent(FVector(BoxCollider->GetUnscaledBoxExtent().X, BoxCollider->GetUnscaledBoxExtent().Y, currentZ / 2), true);
	BoxTrigger->SetRelativeLocation(FVector(20, 0, currentZ/2));
	BoxTrigger->SetBoxExtent(FVector(BoxTrigger->GetUnscaledBoxExtent().X, BoxTrigger->GetUnscaledBoxExtent().Y, currentZ/2), true);
}
//Instantiate a ladder component and return it
UStaticMeshComponent* ALadderTool::GenLadderComponent(UStaticMesh* mesh, float zPos, FName name)
{
	UStaticMeshComponent* StaticMeshComponent = ConstructObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass(), this, name);
	if (StaticMeshComponent)
	{
		StaticMeshComponent->bAutoRegister = true;
		StaticMeshComponent->StaticMesh = mesh;
		StaticMeshComponent->AddLocalTransform(FTransform(FVector(0, 0, zPos)));
		StaticMeshComponent->RegisterComponent();
		StaticMeshComponent->Activate();
		StaticMeshComponent->AttachTo(RootComponent);
		AddOwnedComponent(StaticMeshComponent);
		return StaticMeshComponent;
	}
	return NULL;
}