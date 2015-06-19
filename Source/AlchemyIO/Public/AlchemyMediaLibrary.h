// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GenericPlatformFile.h"
#include "Engine.h"
#include "AlchemyMediaLibrary.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ALCHEMYIO_API AAlchemyMediaLibrary : public AActor
{
	GENERATED_BODY()

	TArray<FString> FileAndFolderPaths(const FString path, const FString wildCard, bool getFiles, bool getDirectories);

public:
	AAlchemyMediaLibrary(const FObjectInitializer& ObjectInitializer);
	UFUNCTION(BlueprintCallable, Category="Media")
	TArray<FString> FilesAtPath(const FString path, const FString wildCard);
	UFUNCTION(BlueprintCallable, Category = "Media")
	TArray<FString> DirectoriesAtPath(const FString path);
};
