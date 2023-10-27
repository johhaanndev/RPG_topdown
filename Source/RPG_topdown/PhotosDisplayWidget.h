// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PhotosDisplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_TOPDOWN_API UPhotosDisplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPhotosDisplayWidget(const FObjectInitializer& ObjectInitializer);

public:
    UPROPERTY(EditAnywhere)
    class UImage* ImageWidget;

    void InitializePhotosArray();

private:
    TArray<FString> PhotosArray;
};
