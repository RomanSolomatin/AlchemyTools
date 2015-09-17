//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

/*
/This code comes from the following source https://wiki.unrealengine.com/Dynamic_Load_Object
*/

#pragma once
#include "GenericPlatformFile.h"
#include "PlatformFilemanager.h"
#include "Developer/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Developer/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"
#include "PlatformFileManager.h"
#include "Engine.h"
#include "LoadAsset.generated.h"

UCLASS()
class ALCHEMYIO_API ULoadAsset : public UObject
{
	GENERATED_BODY()

public:

	ULoadAsset(const FObjectInitializer& ObjectInitializer);
	UFUNCTION(BlueprintCallable, Category = "Media")
	static FName GetObjPath(const UObject* Obj);

	//TEMPLATE Load Obj From Path
	template <typename ObjClass>
	static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;
		//~

		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
	}

	// Load PS From Path 
	UFUNCTION(BlueprintCallable, Category = "Media")
	static UParticleSystem* LoadPSFromPath(const FName& Path);

	// Load Material From Path 
	UFUNCTION(BlueprintCallable, Category = "Media")
	static UMaterialInterface* LoadMatFromPath(const FName& Path);

	// Load Static Mesh From Path 
	UFUNCTION(BlueprintCallable, Category = "Media")
	static UStaticMesh* LoadMeshFromPath(const FName& Path);
};