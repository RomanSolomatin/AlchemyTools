//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

#include "AlchemyIO.h"
#include "GenericPlatformFile.h"
#include "GatherFilesVisitor.h"

bool FGatherFilesVisitor::Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
{
	FString fileOrDirectory = FString(FilenameOrDirectory);
	if (!bIsDirectory && bFiles)
		if (WildCard.IsEmpty()) 
			Result.Add(*fileOrDirectory);
		else
			if (fileOrDirectory.MatchesWildcard(WildCard))
				Result.Add(*fileOrDirectory);
	if (bIsDirectory && bDirectories) Result.Add(*fileOrDirectory);
	return true;
}