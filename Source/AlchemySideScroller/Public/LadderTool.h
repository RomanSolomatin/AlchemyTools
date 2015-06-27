//The MIT License(MIT)
//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

#pragma once

#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "LadderTool.generated.h"

/*
*A ladder generation tool
*/
UCLASS()
class ALCHEMYSIDESCROLLER_API ALadderTool : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ladder, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collider, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collider, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* LadderFrontDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ladder", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* LadderUpHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LadderParts, meta = (AllowPrivateAccess = "true"))
	class UStaticMesh* LadderTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LadderParts, meta = (AllowPrivateAccess = "true"))
	class UStaticMesh* LadderRungs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LadderParts, meta = (AllowPrivateAccess = "true"))
	class UStaticMesh* LadderBottom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LadderParts, meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMeshComponent*> LadderComponentArray;

protected:
	UStaticMeshComponent* GenLadderComponent(UStaticMesh* mesh, float zPos, FName name);

public:	
	//Constructor
	ALadderTool();
	//Called any time a variable is changed
	void OnConstruction(const FTransform& Transform) override;
};
