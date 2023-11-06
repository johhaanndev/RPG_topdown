// Fill out your copyright notice in the Description page of Project Settings.


#include "PhotographerGameMode.h"
#include "HAL/PlatformFilemanager.h"

void APhotographerGameMode::InitializePhotoManagement(FString PhotoManagementFile)
{
	if (FPaths::FileExists(*PhotoManagementFile))
	{
		UE_LOG(LogTemp, Warning, TEXT("PhotosManagement text file found"));
		FString FileContent = "";
		if (!FFileHelper::LoadFileToString(FileContent, *PhotoManagementFile))
		{
			UE_LOG(LogTemp, Error, TEXT("Error trying to read the content. File: %s"), *PhotoManagementFile);
			return;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Initial File Content:\n%s"), *FileContent);
			AllPhotosString = FileContent;
			AllPhotosString.ParseIntoArray(PhotosArray, TEXT(","), true);
			UE_LOG(LogTemp, Warning, TEXT("Initial Array count: %d"), PhotosArray.Num());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PhotosManagement NOT found on route %s. Proceed to create file"), *PhotoManagementFile);
	}
}

void APhotographerGameMode::AddPhoto(FString PathToFile, FString FileName)
{
	AddPhotoToPhotosArray(PathToFile + FileName + ".png");

}

void APhotographerGameMode::AddPhotoToPhotosArray(FString stringValue)
{
	PhotosArray.Add(stringValue);
	AppendPhotoToFile(PhotosManagementFile, stringValue);
	UE_LOG(LogTemp, Warning, TEXT("Photo added to list. Number of elements: %d"), PhotosArray.Num());
}

void APhotographerGameMode::RemovePhotoFromPhotosArray(FString PhotoName)
{
	PhotosArray.Remove(PhotoName);
	UE_LOG(LogTemp, Warning, TEXT("Photo removed from list. Number of elements: %d"), PhotosArray.Num());
}

void APhotographerGameMode::AppendPhotoToFile(FString PhotoManagementFile, FString FileToAdd)
{
	AllPhotosString = ReadContentFromFile(PhotoManagementFile);
	if (AllPhotosString != "ERROR")
	{
		AllPhotosString = AllPhotosString.IsEmpty() ? FileToAdd : AllPhotosString + TEXT(",") + FileToAdd;
		UE_LOG(LogTemp, Warning, TEXT("Append() AllPhotosString content = %s"), *AllPhotosString);

		if (FFileHelper::SaveStringToFile(AllPhotosString, *PhotoManagementFile))
		{
			UE_LOG(LogTemp, Warning, TEXT("succesfully added photo file name = %s"), *AllPhotosString);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Append() Unable to add content to file %s"), *PhotoManagementFile);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Append() Unable to read content from file %s"), *PhotoManagementFile);
	}
}

void APhotographerGameMode::RemovePhotoFromFile(FString PhotoManagementFile, FString FileToRemove)
{
}

FString APhotographerGameMode::ReadContentFromFile(FString PhotoManagementFile)
{
	if (FPaths::FileExists(*PhotoManagementFile))
	{
		FString FileContent = "";
		if (!FFileHelper::LoadFileToString(FileContent, *PhotoManagementFile))
		{
			return "ERROR";
		}
		else
		{
			return FileContent;
		}
	}
	else
	{
		return "ERROR";
	}
}
