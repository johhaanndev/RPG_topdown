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
	void InitializePhotoManagement(FString PhotoManagementFile);

	void AddPhoto(FString PathToFile, FString FileName);
	void AddPhotoToPhotosArray(FString PhotoName);
	void RemovePhotoFromPhotosArray(FString PhotoName);
	int32 GetNumberOfPhotos() { return PhotosArray.Num(); }
	TArray<FString> GetPhotosArray() { return PhotosArray; }
	FString GetPhotosArraySerialized() { return AllPhotosString; }

	void AppendPhotoToFile(FString PhotoManagementFile, FString FileName);
	void RemovePhotoFromFile(FString PhotoManagementFile, FString Filename);
	FString ReadContentFromFile(FString PhotoManagementFile);

private:
	TArray<FString> PhotosArray;
	int NumPhotos = 0;
	FString AllPhotosString;

	UPROPERTY(VisibleAnywhere)
	FString PhotosManagementFile = FPaths::ProjectDir() / TEXT("PhotosManagement/PhotosTextFile.txt");
};
