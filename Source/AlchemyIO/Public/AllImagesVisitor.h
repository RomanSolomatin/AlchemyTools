//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

#pragma once
#include "GenericPlatformFile.h"
#include "Engine.h"


/**
 * 
 */
class ALCHEMYIO_API FAllImagesVisitor : public IPlatformFile::FDirectoryVisitor
{
public:

	TArray<FString>& Result;
	FString WildCard;
	bool bFiles;
	bool bDirectories;
	FAllImagesVisitor(TArray<FString>& InResult, const FString& InWildCard, bool bInFiles, bool bInDirectories)
		: Result(InResult)
		, WildCard(InWildCard)
		, bFiles(bInFiles)
		, bDirectories(bInDirectories)
	{
	}
	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override;
};;
