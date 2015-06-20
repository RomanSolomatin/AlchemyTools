//Copyright(c) 2015 Andrew Armbruster
//Please see included README for LICENSE agreement

#pragma once

#include "Object.h"
#include "FileSystem.generated.h"

/**
 * FileSystem is used for getting lists of directories and files at a give path
 */
UCLASS()
class ALCHEMYIO_API UFileSystem : public UObject
{
	GENERATED_BODY()

protected:
	static TArray<FString> FileAndFolderPaths(const FString path, const FString wildCard, bool getFiles, bool getDirectories);

public:
	/*
	Get files paths at path with the specified wildcard.
	Currently only accepts one wildcard.
	*/
	UFUNCTION(BlueprintCallable, Category = "Media")
	static TArray<FString> FilesAtPath(const FString path, const FString wildCard, bool contentDirAsRoot);
	/*
	Get directories at path.
	*/
	UFUNCTION(BlueprintCallable, Category = "Media")
	static TArray<FString> DirectoriesAtPath(const FString path, bool contentDirAsRoot);
};
