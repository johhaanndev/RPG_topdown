// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class RPG_TOPDOWN_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	bool ShowPhotoDisplayHUD();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PhotosDisplayClass;

	UPROPERTY(EditAnywhere)
	UUserWidget* PhotosDisplay;

	UPROPERTY(VisibleAnywhere)
	FString PhotosManagementFile = FPaths::ProjectDir() / TEXT("PhotosManagement/PhotosTextFile.txt");
};
