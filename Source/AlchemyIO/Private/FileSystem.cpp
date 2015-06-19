// Fill out your copyright notice in the Description page of Project Settings.

#include "AlchemyIO.h"
#include "FileSystem.h"

TArray<FString> UFileSystem::FilesPaths(const FString path, const FString wildCard)
{
	return FileAndFolderPaths(path, wildCard, true, false);
}

TArray<FString> UFileSystem::DirectoriesPaths(const FString path)
{
	return FileAndFolderPaths(path, FString(""), false, true);
}

TArray<FString> UFileSystem::FileAndFolderPaths(const FString path, const FString wildCard, bool getFiles, bool getDirectories)
{
	TArray<FString> result;
	FAllImagesVisitor visitor(result, wildCard, getFiles, getDirectories);
	FPlatformFileManager* manager = new FPlatformFileManager();
	FString FullTexturePath = path;
	manager->Get().GetPlatformFile().IterateDirectory(*FullTexturePath, visitor);
	return result;
}