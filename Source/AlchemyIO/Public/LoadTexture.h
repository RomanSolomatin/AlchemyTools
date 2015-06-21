//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement
//The code in this file is word for word from another online source but I'm now unable to find url or person(s) to give credit. I'll include that as soon as I find it

#pragma once
#include "GenericPlatformFile.h"
#include "PlatformFilemanager.h"
#include "Developer/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Developer/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"
#include "PlatformFileManager.h"
#include "DDSLoader.h"
#include "ImageUtils.h"
#include "Engine.h"
#include "LoadTexture.generated.h"


UENUM(BlueprintType)
enum class EImageExt : uint8
{
	/** Portable Network Graphics */
	PNG				UMETA(DisplayName = "PNG"),

	/** Joint Photographic Experts Group */
	JPEG			UMETA(DisplayName = "JPEG"),

	/** Single channel jpeg */
	GrayscaleJPEG	UMETA(DisplayName = "GrayscaleJPEG"),

	/** Windows Bitmap */
	BMP				UMETA(DisplayName = "BMP"),

	/** Windows Icon resource */
	ICO				UMETA(DisplayName = "ICO"),

	/** OpenEXR (HDR) image file format */
	EXR				UMETA(DisplayName = "EXR"),

	/** Mac icon */
	ICNS			UMETA(DisplayName = "ICNS")
};

/**
Load a dds or image texture at runtime
*/
UCLASS()
class ALCHEMYIO_API ULoadTexture : public UObject
{
	GENERATED_BODY()

public:

	ULoadTexture(const FObjectInitializer& ObjectInitializer);

	/*
	Load a dds texture file by name(ie: full path)
	*/
	UFUNCTION(BlueprintCallable, Category = "Media")
	static UTexture2D* LoadDDS(FString TextureFilename);
	
	/*
	Load an image file by name(ie: full path)
	*/
	UFUNCTION(BlueprintCallable, Category = "Media")
	static UTexture2D* LoadFile(FString FTextureFilename, EImageExt ImageExt);
};