// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "PhotographerGameMode.h"
#include "PlayerCharacterController.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameState = GameStates::Exploring;
	UE_LOG(LogTemp, Warning, TEXT("Initial state: %d"), GameState);
	SetActorRotation(CurrentRotation);

	MainCamera = Cast<UCameraComponent>(GetDefaultSubobjectByName(TEXT("TopDown_Camera")));
	CameraSpringArm = Cast<USpringArmComponent>(GetDefaultSubobjectByName(TEXT("CameraSpringArm")));

	if (MainCamera == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("MainCamera NULL POINTER"));
	if (CameraSpringArm == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("CameraSpringArm NULL POINTER"));


	TopDownCameraLocation = MainCamera->GetComponentLocation();
	TopDownCameraRotation = MainCamera->GetComponentRotation();
	PhotoCameraRotation = FRotator::ZeroRotator;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateCharacter(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveVertical"), this, &APlayerCharacter::MoveVertical);
	PlayerInputComponent->BindAxis(TEXT("MoveHorizontal"), this, &APlayerCharacter::MoveHorizontal);

	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &APlayerCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &APlayerCharacter::LookRightRate);

	PlayerInputComponent->BindAxis(TEXT("ZoomIn"), this, &APlayerCharacter::ZoomIn);
	PlayerInputComponent->BindAxis(TEXT("Zoomout"), this, &APlayerCharacter::ZoomOut);

	PlayerInputComponent->BindAction(TEXT("PhotoMode"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SwitchPhotoMode);
	PlayerInputComponent->BindAction(TEXT("TakePhoto"), EInputEvent::IE_Pressed, this, &APlayerCharacter::TakePhoto);

	PlayerInputComponent->BindAction(TEXT("ShowPhotoDisplayHUD"), EInputEvent::IE_Pressed, this, &APlayerCharacter::ShowPhotosDisplayHUD);
	PlayerInputComponent->BindAction(TEXT("NextPhoto"), EInputEvent::IE_Pressed, this, &APlayerCharacter::NextPhoto);
	PlayerInputComponent->BindAction(TEXT("PrevPhoto"), EInputEvent::IE_Pressed, this, &APlayerCharacter::PreviousPhoto);
}

void APlayerCharacter::MoveVertical(float AxisValue)
{
	if (!IsPhotoMode && GameState == GameStates::Exploring)
	{
		FVector VerticalMovement = FVector::ForwardVector * AxisValue;
		if (VerticalMovement.Length() > 0.25f)
		{
			AddMovementInput(VerticalMovement);
		}
	}
}

void APlayerCharacter::MoveHorizontal(float AxisValue)
{
	if (!IsPhotoMode && GameState == GameStates::Exploring)
	{
		FVector HorizontalMovement = FVector::RightVector * AxisValue;
		if (HorizontalMovement.Length() > 0.25f)
		{
			AddMovementInput(HorizontalMovement);
		}
	}
}

void APlayerCharacter::RotateCharacter(float DeltaTime)
{
	if (!IsPhotoMode && GameState == GameStates::Exploring)
	{
		FVector Velocity = GetVelocity().GetSafeNormal();
		if (FMath::Abs(Velocity.X) > 0.2f || FMath::Abs(Velocity.Y) > 0.2f)
		{
			CurrentRotation = Velocity.Rotation();
		}
		SetActorRotation(CurrentRotation);
	}
}

void APlayerCharacter::LookUpRate(float AxisValue)
{
	if (IsPhotoMode && GameState == GameStates::Exploring)
	{
		FRotator NewRotation = CameraSpringArm->GetRelativeRotation();
		NewRotation.Pitch += -AxisValue * RotationRate * GetWorld()->GetDeltaSeconds();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch, -85.f, 85.f);
		CameraSpringArm->SetRelativeRotation(NewRotation);
	}
}

void APlayerCharacter::LookRightRate(float AxisValue)
{
	if (IsPhotoMode && GameState == GameStates::Exploring)
	{
		FRotator NewRotation = CameraSpringArm->GetRelativeRotation();
		NewRotation.Yaw += AxisValue * RotationRate * GetWorld()->GetDeltaSeconds();
		
		CameraSpringArm->SetRelativeRotation(NewRotation);
	}
}

void APlayerCharacter::ZoomIn(float AxisValue)
{
	if (IsPhotoMode && GameState == GameStates::Exploring)
	{
		CurrentFOV -= ZoomSpeed * AxisValue;
		CurrentFOV = FMath::Clamp(CurrentFOV, MinFOV, InitialFOV);
		MainCamera->SetFieldOfView(CurrentFOV);
	}
}

void APlayerCharacter::ZoomOut(float AxisValue)
{
	if (IsPhotoMode && GameState == GameStates::Exploring)
	{
		CurrentFOV += ZoomSpeed * AxisValue;
		CurrentFOV = FMath::Clamp(CurrentFOV, MinFOV, InitialFOV);
		MainCamera->SetFieldOfView(CurrentFOV);
	}
}

void APlayerCharacter::SwitchPhotoMode()
{
	if (GameState == GameStates::PhotoDisplaying)
	{
		UE_LOG(LogTemp, Warning, TEXT("PhotoMode is unavailable. Disable HUD first."));
		return;
	}

	IsPhotoMode = !IsPhotoMode;

	if (IsPhotoMode)
	{
		CameraSpringArm->TargetArmLength = -10.f;
		CurrentFOV = 90.0f;
		MainCamera->SetFieldOfView(InitialFOV);
		PhotoCameraRotation = GetActorRotation();
		CameraSpringArm->SetRelativeRotation(PhotoCameraRotation);
		MaxRotationAngle = CameraSpringArm->GetRelativeRotation().Yaw - RotationAngleBoundaries;
	}
	else
	{
		CameraSpringArm->TargetArmLength = 1000.f;
		MainCamera->SetFieldOfView(InitialFOV);
		CameraSpringArm->SetRelativeRotation(TopDownCameraRotation);
	}

	UE_LOG(LogTemp, Warning, TEXT("Switched to state: %d"), GameState);
}

void APlayerCharacter::TakePhoto()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController && IsPhotoMode && GameState == GameStates::Exploring)
	{
		IFileManager& FileManager = IFileManager::Get();
		FString now = FDateTime::Now().ToString(TEXT("%Y%m%d%H%M%S"));
		FString FullFilePath = PhotosDirectory + "/" + now;

		FString FileName = "photo_" + now;

		FString Command = FString::Printf(TEXT("HighResShot 1920x1080 filename=%s"), *FileName);
		PlayerController->ConsoleCommand(Command, true);

		//FPlatformProcess::Sleep(2.0f);
		APhotographerGameMode* GameMode = GetWorld()->GetAuthGameMode<APhotographerGameMode>();
		GameMode->AddPhoto(FPaths::ScreenShotDir(), FileName);

		// Mueve el archivo a la ruta de destino.
		/*if (FileManager.Move(*FullFilePath, *FPaths::ScreenShotDir()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Photo saved succesfully on: %s"), *FullFilePath);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Error saving the photo"));
		}*/
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Photo only available on PhotoMode and if photo display is disabled"));
	}
}

void APlayerCharacter::ShowPhotosDisplayHUD()
{
	UE_LOG(LogTemp, Warning, TEXT("ShowPhotosDisplayHUD from APlayerCharacter.cpp"));
	APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(GetController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("PlayerController found: %s"), *PlayerController->GetName());

	UE_LOG(LogTemp, Warning, TEXT("Switched to state: %d"), GameState);
	if (PlayerController->ShowPhotoDisplayHUD())
		GameState = GameStates::PhotoDisplaying;
	else
		GameState = GameStates::Exploring;
}

void APlayerCharacter::NextPhoto()
{
	if (GameState != GameStates::PhotoDisplaying)
	{
		UE_LOG(LogTemp, Warning, TEXT("NextPhoto only available when PhotoDisplaying"));
		return;
	}

	APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(GetController());
	if (PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Next Photo"));
		PlayerController->BrowsePhoto(true);
	}
}

void APlayerCharacter::PreviousPhoto()
{
	if (GameState != GameStates::PhotoDisplaying)
	{
		UE_LOG(LogTemp, Warning, TEXT("NextPhoto only available when PhotoDisplaying"));
		return;
	}

	APlayerCharacterController* PlayerController = Cast<APlayerCharacterController>(GetController());
	if (PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Previous Photo"));
		PlayerController->BrowsePhoto(false);
	}
}

