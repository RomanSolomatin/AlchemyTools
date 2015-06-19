//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

#include "AlchemyIO.h"
#include "GenericPlatformFile.h"
#include "AllImagesVisitor.h"

bool FAllImagesVisitor::Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
{
	FString fileOrDirectory = FString(FilenameOrDirectory);
	if (!bIsDirectory && bFiles)
	{
		if (WildCard.IsEmpty())
		{
			Result.Add(*fileOrDirectory);
			return true;
		}
		else
		{
			if (fileOrDirectory.MatchesWildcard(WildCard))
			{
				Result.Add(*fileOrDirectory);
				return true;
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("not a file"));
	if (bIsDirectory && bDirectories)
	{
		Result.Add(*fileOrDirectory);
		return true;
	}
	return true;
}