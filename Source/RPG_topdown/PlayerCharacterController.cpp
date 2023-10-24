// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "Blueprint/UserWidget.h"

void APlayerCharacterController::BeginPlay()
{
	
}

void APlayerCharacterController::ShowPhotoDisplayHUD()
{
	if (PhotosDisplay)
	{
		UE_LOG(LogTemp, Warning, TEXT("Photos Display is already enabled"));
		PhotosDisplay->RemoveFromViewport();
		PhotosDisplay = nullptr;
		return;
	}

	PhotosDisplay = CreateWidget(this, PhotosDisplayClass);
	if (PhotosDisplay != nullptr)
	{
		PhotosDisplay->AddToViewport();
	}
}

