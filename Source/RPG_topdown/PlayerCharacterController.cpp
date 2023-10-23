// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "Blueprint/UserWidget.h"

void APlayerCharacterController::BeginPlay()
{
	
}

void APlayerCharacterController::ShowPhotoDisplayHUD()
{
	UE_LOG(LogTemp, Warning, TEXT("Show Photo display HUD"));
	UUserWidget* PhotosDisplayScreen = CreateWidget(this, PhotosDisplayClass);
	if (PhotosDisplayScreen != nullptr)
	{
		PhotosDisplayScreen->AddToViewport();
	}
}

