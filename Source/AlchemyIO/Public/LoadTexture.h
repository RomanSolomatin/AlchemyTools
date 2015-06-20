// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Developer/ImageWrapper/Public/Interfaces/IImageWrapper.h"

/**
*
*/
class ALCHEMYIO_API ULoadTexture : public UObject
{
public:
	/*
	Load a dds texture file by name(ie: full path)
	*/
	UFUNCTION(BlueprintCallable, Category = "Media")
	static UTexture2D* LoadDDS(FString TextureFilename);

	/*
	Load an image file by name(ie: full path)
	*/
	UFUNCTION(BlueprintCallable, Category = "Media")
	static UTexture2D* LoadFile(FString FTextureFilename, EImageFormat::Type ImageFormat);
};