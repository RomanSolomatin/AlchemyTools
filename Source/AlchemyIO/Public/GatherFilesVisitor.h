//Copyright(c) 2015 Andrew Armbruster
//Please see included README for LICENSE agreement

#pragma once
#include "GenericPlatformFile.h"
#include "Engine.h"


/**
 * Visitor for getting list of directories and files in a given path
 */
class ALCHEMYIO_API FGatherFilesVisitor : public IPlatformFile::FDirectoryVisitor
{
public:
	TArray<FString>& Result;
	FString WildCard;
	bool bFiles;
	bool bDirectories;
	FGatherFilesVisitor(TArray<FString>& InResult, const FString& WildCard, bool bFiles, bool bDirectories)
		: Result(InResult)
		, WildCard(WildCard)
		, bFiles(bFiles)
		, bDirectories(bDirectories)
	{
	}
	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override;
};;
