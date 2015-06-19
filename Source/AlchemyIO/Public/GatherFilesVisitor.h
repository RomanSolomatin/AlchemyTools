//Copyright(c) 2015 Andrew Armbruster
//Please see included README for LICENSE agreement

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
	FAllImagesVisitor(TArray<FString>& InResult, const FString& WildCard, bool bFiles, bool bDirectories)
		: Result(InResult)
		, WildCard(WildCard)
		, bFiles(bFiles)
		, bDirectories(bDirectories)
	{
	}
	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override;
};;
