//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement


#include "AlchemyIO.h"
#include "Engine.h"
#include "LoadAsset.h"

ULoadAsset::ULoadAsset(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer){ }


FName ULoadAsset::GetObjPath(const UObject* Obj)
{
	if (!Obj) return NAME_None;
	if (!Obj->IsValidLowLevel()) return NAME_None;
	//~

	FStringAssetReference ThePath = FStringAssetReference(Obj);

	if (!ThePath.IsValid()) return NAME_None;

	//The Class FString Name For This Object
	FString Str = Obj->GetClass()->GetDescription();

	Str += "'";
	Str += ThePath.ToString();
	Str += "'";

	return FName(*Str);
}

UParticleSystem* ULoadAsset::LoadPSFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return LoadObjFromPath<UParticleSystem>(Path);
}


UMaterialInterface* ULoadAsset::LoadMatFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return LoadObjFromPath<UMaterialInterface>(Path);
}

UStaticMesh* ULoadAsset::LoadMeshFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	return LoadObjFromPath<UStaticMesh>(Path);
}