// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

	PlayerInputComponent->BindAction(TEXT("PhotoMode"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SwitchPhotoMode);
}

void APlayerCharacter::MoveVertical(float AxisValue)
{
	if (!IsPhotoMode)
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
	if (!IsPhotoMode)
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
	if (!IsPhotoMode)
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
	if (IsPhotoMode)
	{
		FRotator NewRotation = CameraSpringArm->GetRelativeRotation();
		NewRotation.Pitch += -AxisValue * RotationRate * GetWorld()->GetDeltaSeconds();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch, -85.f, 85.f); // Opcional: Puedes agregar restricciones de límites si lo deseas.
		CameraSpringArm->SetRelativeRotation(NewRotation);
	}
}

void APlayerCharacter::LookRightRate(float AxisValue)
{
	if (IsPhotoMode)
	{
		FRotator NewRotation = CameraSpringArm->GetRelativeRotation();
		NewRotation.Yaw += AxisValue * RotationRate * GetWorld()->GetDeltaSeconds();
		CameraSpringArm->SetRelativeRotation(NewRotation);
	}
}

void APlayerCharacter::SwitchPhotoMode()
{
	IsPhotoMode = !IsPhotoMode;
	UE_LOG(LogTemp, Warning, TEXT("IsPhotoMode = %s"), IsPhotoMode ? TEXT("True") : TEXT("False"));

	if (IsPhotoMode)
	{
		CameraSpringArm->TargetArmLength = -10.f;
		PhotoCameraRotation = GetActorRotation();
		CameraSpringArm->SetRelativeRotation(PhotoCameraRotation);
	}
	else
	{
		CameraSpringArm->TargetArmLength = 1000.f;
		CameraSpringArm->SetRelativeRotation(TopDownCameraRotation);
	}
}


