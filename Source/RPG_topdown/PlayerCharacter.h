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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	TArray<UCameraComponent*> Allcameras;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* MainCamera;

private:
	void MoveVertical(float AxisValue);
	void MoveHorizontal(float AxisValue);
	void RotateCharacter(float DeltaTime);

	void SwitchPhotoMode();

	FRotator CurrentRotation;
	FRotator TargetRotation;

	FVector TopDownCameraLocation;
	FRotator TopDownCameraRotation;

	FRotator PhotoCameraRotation;


	class USpringArmComponent* CameraSpringArm;

	float SpringArmLength;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 0.5f;

	bool IsPhotoMode = false;

};
