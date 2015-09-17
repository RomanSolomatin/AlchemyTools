//Copyright(c) 2015 Andrew Armbruster
//Please read included README for LICENSE agreement
//The code in this file is word for word from another online source but I'm now unable to find url or person(s) to give credit. I'll include that as soon as I find it

#include "AlchemyIO.h"
#include "Engine.h"
#include "Developer/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Developer/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"
#include "DDSLoader.h"
#include "ImageUtils.h"
#include "LoadTexture.h"


ULoadTexture::ULoadTexture(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

/*
Load an image file by name(ie: full path)
*/
UTexture2D* ULoadTexture::LoadFile(FString TextureFilename, EImageExt ImageExt)
{
	// Represents the entire file in memory.
	TArray<uint8> RawFileData;

	if (FFileHelper::LoadFileToArray(RawFileData, *TextureFilename))
	{
		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		uint8 bytes = (uint8)ImageExt;

		EImageFormat::Type ImageFormat = (EImageFormat::Type)ImageExt;

		IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);
		if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
		{
			const TArray<uint8>* UncompressedBGRA = NULL;

			if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
			{
				// Create the UTexture for rendering
				UTexture2D* MyTexture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

				// Fill in the source data from the file

				void* TextureData = MyTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				//MyTexture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(TextureData, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
				MyTexture->PlatformData->Mips[0].BulkData.Unlock();

				// Update the rendering resource from data.
				MyTexture->UpdateResource();
				return MyTexture;
			}
		}
	}
	return NULL;
}

/*
Load a dds texture file by name(ie: full path)
*/
UTexture2D* ULoadTexture::LoadDDS(FString TextureFilename)
{
	UTexture2D* Texture = NULL;

	FString TexturePath = TextureFilename;
	UE_LOG(LogTemp, Warning, TEXT("TexturePath: %s"), *TexturePath)
		TArray<uint8> FileData;

	/* Load DDS texture */
	if (FFileHelper::LoadFileToArray(FileData, *TexturePath, 0))
	{
		FDDSLoadHelper DDSLoadHelper(&FileData[0], FileData.Num());
		if (DDSLoadHelper.IsValid2DTexture())
		{
			int32 NumMips = DDSLoadHelper.ComputeMipMapCount();
			EPixelFormat Format = DDSLoadHelper.ComputePixelFormat();
			int32 BlockSize = 16;

			if (NumMips == 0)
			{
				NumMips = 1;
			}

			if (Format == PF_DXT1)
			{
				BlockSize = 8;
			}

			/* Create transient texture */
			Texture = UTexture2D::CreateTransient(DDSLoadHelper.DDSHeader->dwWidth, DDSLoadHelper.DDSHeader->dwHeight, Format);
			Texture->PlatformData->NumSlices = 1;
			Texture->NeverStream = true;

			/* Get pointer to actual data */
			uint8* DataPtr = (uint8*)DDSLoadHelper.GetDDSDataPointer();

			uint32 CurrentWidth = DDSLoadHelper.DDSHeader->dwWidth;
			uint32 CurrentHeight = DDSLoadHelper.DDSHeader->dwHeight;

			/* Iterate through mips */
			for (int32 i = 0; i < NumMips; i++)
			{
				/* Lock to 1x1 as smallest size */
				CurrentWidth = (CurrentWidth < 1) ? 1 : CurrentWidth;
				CurrentHeight = (CurrentHeight < 1) ? 1 : CurrentHeight;

				/* Get number of bytes to read */
				int32 NumBytes = CurrentWidth * CurrentHeight * 4;
				if (Format == PF_DXT1 || Format == PF_DXT3 || Format == PF_DXT5)
				{
					/* Compressed formats */
					NumBytes = ((CurrentWidth + 3) / 4) * ((CurrentHeight + 3) / 4) * BlockSize;
				}

				/* Write to existing mip */
				if (i < Texture->PlatformData->Mips.Num())
				{
					FTexture2DMipMap& Mip = Texture->PlatformData->Mips[i];

					void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
					FMemory::Memcpy(Data, DataPtr, NumBytes);
					Mip.BulkData.Unlock();
				}

				/* Add new mip */
				else
				{
					FTexture2DMipMap* Mip = new(Texture->PlatformData->Mips) FTexture2DMipMap();
					Mip->SizeX = CurrentWidth;
					Mip->SizeY = CurrentHeight;

					Mip->BulkData.Lock(LOCK_READ_WRITE);
					Mip->BulkData.Realloc(NumBytes);
					Mip->BulkData.Unlock();

					void* Data = Mip->BulkData.Lock(LOCK_READ_WRITE);
					FMemory::Memcpy(Data, DataPtr, NumBytes);
					Mip->BulkData.Unlock();
				}

				/* Set next mip level */
				CurrentWidth /= 2;
				CurrentHeight /= 2;

				DataPtr += NumBytes;
			}

			Texture->UpdateResource();
		}
	}
	return Texture;
}