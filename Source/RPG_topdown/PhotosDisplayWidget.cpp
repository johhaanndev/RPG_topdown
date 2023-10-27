// Fill out your copyright notice in the Description page of Project Settings.


#include "PhotosDisplayWidget.h"
#include "Components/Image.h"


UPhotosDisplayWidget::UPhotosDisplayWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("PhotoPath from constructor: %s"), *PhotoPath);
    LoadImageFromPath();
}

void UPhotosDisplayWidget::LoadImageFromPath()
{
    
}
