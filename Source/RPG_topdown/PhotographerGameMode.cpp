// Fill out your copyright notice in the Description page of Project Settings.


#include "PhotographerGameMode.h"

void APhotographerGameMode::AddPhoto(FString PathToFile, FString FileName)
{
	NumPhotos++;
	AddPhotoToPhotosArray(PathToFile + "/" + FileName);

}

void APhotographerGameMode::AddPhotoToPhotosArray(FString stringValue)
{
	PhotosArray.Add(stringValue);
	UE_LOG(LogTemp, Warning, TEXT("Photo added to list. Number of elements: %d"), PhotosArray.Num());
}

void APhotographerGameMode::RemovePhotoFromPhotosArray(FString PhotoName)
{
	PhotosArray.Remove(PhotoName);
	UE_LOG(LogTemp, Warning, TEXT("Photo removed from list. Number of elements: %d"), PhotosArray.Num());
}

int32 APhotographerGameMode::GetNumberOfPhotos()
{
	return PhotosArray.Num();
}

