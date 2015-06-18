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

public:
	AAlchemyMediaLibrary(const FObjectInitializer& ObjectInitializer);
	UFUNCTION(BlueprintCallable, Category="Media")
	TArray<FString> GetImages(const FString path);
};
