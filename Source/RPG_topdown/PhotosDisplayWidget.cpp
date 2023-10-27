// Fill out your copyright notice in the Description page of Project Settings.


#include "PhotosDisplayWidget.h"
#include "Components/Image.h"
#include "HAL/FileManager.h"


UPhotosDisplayWidget::UPhotosDisplayWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    //UE_LOG(LogTemp, Warning, TEXT("PhotoPath from constructor: %s"), *PhotoPath);
    LoadImageFromPath();
}

void UPhotosDisplayWidget::LoadImageFromPath()
{
    /*IFileManager* _FileManager = &IFileManager::Get();
    TArray<FString> Files;
    const TCHAR* extension = _T("*.png");
    _FileManager->FindFilesRecursive(Files, *PhotoPath, extension, true, false, false);*/

}

void UPhotosDisplayWidget::AddPhotoToPhotosArray(FString PhotoName)
{
    PhotosArray.Add(PhotoName);
}

void UPhotosDisplayWidget::RemovePhotoFromPhotosArray(FString PhotoName)
{
    PhotosArray.Remove(PhotoName);
}
