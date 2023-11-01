// Fill out your copyright notice in the Description page of Project Settings.


#include "PhotosDisplayWidget.h"
#include "Components/Image.h"
#include "HAL/FileManager.h"
#include "Components/Image.h"
#include "ImageUtils.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"

UPhotosDisplayWidget::UPhotosDisplayWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void UPhotosDisplayWidget::InitializePhotosWidget(FString PhotosSerialized)
{
    UE_LOG(LogTemp, Warning, TEXT("InitializePhotosArray"));
    PhotosSerialized.ParseIntoArray(PhotosArray, TEXT(","), true);

    UImage* PhotoViewer = WidgetTree->FindWidget<UImage>(TEXT("Displayer"));
    if (PhotosArray.Num() > 0 && PhotoViewer)
    {
        FString ImagePath = PhotosArray[0];

        UTexture2D* LoadedTexture = LoadTextureFromPath(ImagePath);

        // Asignar la textura a la UImage
        if (LoadedTexture)
        {
            PhotoViewer->SetBrushFromTexture(LoadedTexture);
            UE_LOG(LogTemp, Warning, TEXT("Texture loaded succesfully"));
        }
    }
}

UTexture2D* UPhotosDisplayWidget::LoadTextureFromPath(const FString& ImagePath)
{
    TArray<uint8> ImageData;
    if (FFileHelper::LoadFileToArray(ImageData, *ImagePath))
    {
        // Crear una textura 2D a partir de los datos de imagen
        UTexture2D* Texture = FImageUtils::ImportBufferAsTexture2D(ImageData);

        return Texture;
    }

    return nullptr;
}

void UPhotosDisplayWidget::BrowseNextPhoto(bool IsNext)
{
    UE_LOG(LogTemp, Warning, TEXT("Browsing. PhotosIndex = %d"), PhotosIndex);
    if (IsNext)
    {
        PhotosIndex++;
        if (PhotosIndex >= PhotosArray.Num())
        {
            PhotosIndex = 0;
            UE_LOG(LogTemp, Warning, TEXT("Reached last photo. Restart to PhotosIndex = %d"), PhotosIndex);
        }
    }
    else
    {
        PhotosIndex--;
        if (PhotosIndex < 0)
        {
            PhotosIndex = PhotosArray.Num() - 1;
            UE_LOG(LogTemp, Warning, TEXT("Reached first photo. Dsiplay last photo. PhotosIndex = %d"), PhotosIndex);
        }
    }
    
}
