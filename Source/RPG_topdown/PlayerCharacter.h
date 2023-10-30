// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class RPG_TOPDOWN_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	enum GameStates { Exploring, PhotoDisplaying };
	GameStates GameState;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	TArray<UCameraComponent*> Allcameras;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* MainCamera;

	UPROPERTY(EditAnywhere)
	FString PhotosDirectory = FPaths::ProjectDir() / TEXT("Photos");

private:
	const FString PhotoFilename = FString(TEXT("Photo_"));
	const float RotationAngleBoundaries = 80.f;

	void MoveVertical(float AxisValue);
	void MoveHorizontal(float AxisValue);
	void RotateCharacter(float DeltaTime);

	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void ZoomIn(float AxisValue);
	void ZoomOut(float AxisValue);

	void SwitchPhotoMode();
	void TakePhoto();

	void ShowPhotosDisplayHUD();

	FRotator CurrentRotation;
	FRotator TargetRotation;

	FVector TopDownCameraLocation;
	FRotator TopDownCameraRotation;

	FRotator PhotoCameraRotation;

	class USpringArmComponent* CameraSpringArm;

	float SpringArmLength;
	
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 2.f;
	
	UPROPERTY(EditAnywhere)
	float RotationRate = 50.f;
	
	float MaxRotationAngle;

	UPROPERTY(EditAnywhere)
	float ZoomSpeed = 0.5f;

	UPROPERTY(EditAnywhere)
	float InitialFOV = 90.f;

	UPROPERTY(EditAnywhere)
	float MinFOV = 35.f;

	float CurrentFOV;

	bool IsPhotoMode = false;

};
