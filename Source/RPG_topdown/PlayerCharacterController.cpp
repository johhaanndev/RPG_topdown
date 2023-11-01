// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "Blueprint/UserWidget.h"
#include "PhotographerGameMode.h"
#include "PhotosDisplayWidget.h"

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
	if (PhotosDisplayWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Photos Display is already enabled"));
		PhotosDisplayWidget->RemoveFromViewport();
		PhotosDisplayWidget = nullptr;
		return false;
	}

	PhotosDisplayWidget = Cast<UPhotosDisplayWidget>(CreateWidget(this, PhotosDisplayWidgetClass));
	if (PhotosDisplayWidget != nullptr)
	{
		APhotographerGameMode* GameMode = GetWorld()->GetAuthGameMode<APhotographerGameMode>();
		UE_LOG(LogTemp, Warning, TEXT("Show display enabled. Number of photos to show: %d"), GameMode->GetNumberOfPhotos());
		PhotosDisplayWidget->InitializePhotosWidget(GameMode->GetPhotosArraySerialized());
		PhotosDisplayWidget->AddToViewport();
	}
	return true;
}

void APlayerCharacterController::BrowsePhoto(bool IsNext)
{
	if (PhotosDisplayWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Display found, browsing..."));
		PhotosDisplayWidget->BrowseNextPhoto(IsNext);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Photos Display not found"));
	}
}

