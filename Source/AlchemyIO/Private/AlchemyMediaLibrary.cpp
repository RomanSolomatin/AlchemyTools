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

TArray<FString> AAlchemyMediaLibrary::FilesAtPath(const FString path, const FString wildCard )
{
	return FileAndFolderPaths(path, wildCard, true, false);
}

TArray<FString> AAlchemyMediaLibrary::DirectoriesAtPath(const FString path)
{
	return FileAndFolderPaths(path, FString(""), false, true);
}

TArray<FString> AAlchemyMediaLibrary::FileAndFolderPaths(const FString path, const FString wildCard, bool getFiles, bool getDirectories)
{
	TArray<FString> result;
	FAllImagesVisitor visitor(result, wildCard, getFiles, getDirectories);
	FPlatformFileManager* manager = new FPlatformFileManager();
	FString FullTexturePath = path;
	manager->Get().GetPlatformFile().IterateDirectory(*FullTexturePath, visitor);
	return result;
}
