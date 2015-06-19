//Copyright(c) 2015 Andrew Armbruster
//Please see included README for LICENSE agreement

#pragma once

#include "Object.h"
#include "FileSystem.generated.h"

/**
 * 
 */
UCLASS()
class ALCHEMYIO_API UFileSystem : public UObject
{
	GENERATED_BODY()
	
	TArray<FString> FileAndFolderPaths(const FString path, const FString wildCard, bool getFiles, bool getDirectories);

public:
	UFUNCTION(BlueprintCallable, Category = "Media")
	static TArray<FString> FilesAtPath(const FString path, const FString wildCard);
	UFUNCTION(BlueprintCallable, Category = "Media")
	static TArray<FString> DirectoriesAtPath(const FString path);
};
