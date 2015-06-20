//Copyright(c) 2015 Andrew Armbruster
//Please see included README for LICENSE agreement

#include "AlchemyIO.h"
#include "GatherFilesVisitor.h"
#include "FileSystem.h"

//Get files paths at path with the specified wildcard.
//Currently only accepts one wildcard.
TArray<FString> UFileSystem::FilesAtPath(const FString path, const FString wildCard, bool contentDirAsRoot)
{
	return UFileSystem::FileAndFolderPaths(contentDirAsRoot ? FPaths::GameContentDir() + path : path, wildCard, true, false);
}
//Get list of directories paths at the given path.
TArray<FString> UFileSystem::DirectoriesAtPath(const FString path, bool contentDirAsRoot)
{
	return UFileSystem::FileAndFolderPaths(contentDirAsRoot ? FPaths::GameContentDir() + path : path, FString(""), false, true);
}

TArray<FString> UFileSystem::FileAndFolderPaths(const FString path, const FString wildCard, bool getFiles, bool getDirectories)
{
	TArray<FString> result;
	FGatherFilesVisitor visitor = FGatherFilesVisitor(result, wildCard, getFiles, getDirectories);
	FPlatformFileManager* manager = new FPlatformFileManager();
	FString FullTexturePath = path;
	manager->Get().GetPlatformFile().IterateDirectory(*FullTexturePath, visitor);
	return result;
}