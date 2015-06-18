//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

#include "AlchemyIO.h"
#include "GenericPlatformFile.h"
#include "AllImagesVisitor.h"

bool FAllImagesVisitor::Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
{
	FString fileOrDirectory = FString(FilenameOrDirectory);
	//if (!bIsDirectory)
	//{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *fileOrDirectory);
		Result.Add(*fileOrDirectory);
		//Images.Add(*fileOrDirectory);
		return true;
	//}
	//return false;
}