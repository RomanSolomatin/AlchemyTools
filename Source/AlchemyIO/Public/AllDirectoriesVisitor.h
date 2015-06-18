//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement

#pragma once
#include "GenericPlatformFile.h"
#include "Engine.h"

/**
*
*/
class ALCHEMYIO_API AllDirectoriesVisitor : public IPlatformFile::FDirectoryVisitor
{

public:
	TArray<FString> Directories;
	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override;
};
