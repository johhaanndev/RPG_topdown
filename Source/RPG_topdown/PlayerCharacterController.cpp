// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "Blueprint/UserWidget.h"
#include "PhotographerGameMode.h"

void APlayerCharacterController::BeginPlay()
{
	APhotographerGameMode* GameMode = GetWorld()->GetAuthGameMode<APhotographerGameMode>();
	if (GameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GameMode not found"));
		return;
	}
	
	GameMode->InitializePhotoManagement(*PhotosManagementFile);
}

bool APlayerCharacterController::ShowPhotoDisplayHUD()
{
	if (PhotosDisplay)
	{
		UE_LOG(LogTemp, Warning, TEXT("Photos Display is already enabled"));
		PhotosDisplay->RemoveFromViewport();
		PhotosDisplay = nullptr;
		return false;
	}

	PhotosDisplay = CreateWidget(this, PhotosDisplayClass);
	if (PhotosDisplay != nullptr)
	{
		APhotographerGameMode* GameMode = GetWorld()->GetAuthGameMode<APhotographerGameMode>();
		UE_LOG(LogTemp, Warning, TEXT("Show display enabled. Number of photos to show: %d"), GameMode->GetNumberOfPhotos());
		PhotosDisplay->AddToViewport();
	}
	return true;
}

