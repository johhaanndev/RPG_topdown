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
    void InitializePhotosWidget(FString PhotosSerialized);
    void SetTextureToBrush(int32 Index);

    UTexture2D* LoadTextureFromPath(const FString& ImagePath);

    void BrowseNextPhoto(bool IsNext);
    
private:

    TArray<FString> PhotosArray;
    int32 PhotosIndex = 0;
};
