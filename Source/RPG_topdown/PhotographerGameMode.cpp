// Fill out your copyright notice in the Description page of Project Settings.


#include "PhotographerGameMode.h"

void APhotographerGameMode::AddPhoto()
{
	NumPhotos++;

	UE_LOG(LogTemp, Warning, TEXT("Number of Photos taken: %d"), NumPhotos);

}
