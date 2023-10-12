// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"

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
	SetActorRotation(CurrentRotation);

	//MainCamera = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()));
	MainCamera = Cast<UCameraComponent>(GetDefaultSubobjectByName(TEXT("TopDown_Camera")));
	PhotoCamera = Cast<UCameraComponent>(GetDefaultSubobjectByName(TEXT("PhotoMode_Camera")));

	if (MainCamera == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("MainCamera NULL POINTER"));

	if (PhotoCamera == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("PhotoCamera NULL POINTER"));
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

	PlayerInputComponent->BindAction(TEXT("PhotoMode"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SwitchPhotoMode);
}

void APlayerCharacter::MoveVertical(float AxisValue)
{
	FVector VerticalMovement = FVector::ForwardVector * AxisValue;
	if (VerticalMovement.Length() > 0.25f)
	{
		AddMovementInput(VerticalMovement);
	}
}

void APlayerCharacter::MoveHorizontal(float AxisValue)
{
	FVector HorizontalMovement = FVector::RightVector * AxisValue;
	if (HorizontalMovement.Length() > 0.25f)
	{
		AddMovementInput(HorizontalMovement);
	}
}

void APlayerCharacter::RotateCharacter(float DeltaTime)
{
	FVector Velocity = GetVelocity().GetSafeNormal();
	if (FMath::Abs(Velocity.X) > 0.2f || FMath::Abs(Velocity.Y) > 0.2f)
	{
		CurrentRotation = Velocity.Rotation();
	}
	SetActorRotation(CurrentRotation);
}

void APlayerCharacter::SwitchPhotoMode()
{
	IsPhotoMode = !IsPhotoMode;
	UE_LOG(LogTemp, Warning, TEXT("IsPhotoMode = %s"), IsPhotoMode ? TEXT("True") : TEXT("False"));
}


