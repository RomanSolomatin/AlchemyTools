// Fill out your copyright notice in the Description page of Project Settings.

#include "AlchemyIO.h"
#include "AlchemyIO.h"
#include "AlchemyPathTool.h"
#include "AllDirectoriesVisitor.h"
#include "AllImagesVisitor.h"
#include "PlatformFileManager.h"
#include "Engine.h"
#include "Developer/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Developer/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"
#include "DDSLoader.h"
#include "ImageUtils.h"
#include "AlchemyMediaLibrary.h"

AAlchemyMediaLibrary::AAlchemyMediaLibrary(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}


TArray<FString> AAlchemyMediaLibrary::GetImages(const FString path)
{
	UE_LOG(LogTemp, Warning, TEXT("GetImages!"));
	TArray<FString> images;
	FAllImagesVisitor visitor(images, FString(".jpeg"), true, false);
	FPlatformFileManager* manager = new FPlatformFileManager();
	FString FullTexturePath = path;
	// FPaths::GameContentDir() + path;
	manager->Get().GetPlatformFile().IterateDirectory(*FullTexturePath, visitor);
	return images;
}
