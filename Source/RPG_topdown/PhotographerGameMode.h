// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PhotographerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RPG_TOPDOWN_API APhotographerGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void AddPhoto(FString PathToFile, FString FileName);
	void AddPhotoToPhotosArray(FString PhotoName);
	void RemovePhotoFromPhotosArray(FString PhotoName);
	int32 GetNumberOfPhotos();

private:
	TArray<FString> PhotosArray;
	int NumPhotos = 0;
};
