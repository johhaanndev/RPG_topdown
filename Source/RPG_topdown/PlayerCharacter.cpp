// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

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
	//UE_LOG(LogTemp, Warning, TEXT("Current rotation = %s vs ActorRotation = %s"), *CurrentRotation.ToString(), *GetActorRotation().ToString());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Velocity = GetVelocity().GetSafeNormal();
	if (FMath::Abs(Velocity.X) > 0.2f || FMath::Abs(Velocity.Y) > 0.2f)
	{
		CurrentRotation = Velocity.Rotation();
	}
	SetActorRotation(CurrentRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Current rotation = %s vs ActorRotation = %s"), *CurrentRotation.ToString(), *GetActorRotation().ToString());
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveVertical"), this, &APlayerCharacter::MoveVertical);
	PlayerInputComponent->BindAxis(TEXT("MoveHorizontal"), this, &APlayerCharacter::MoveHorizontal);
}

void APlayerCharacter::MoveVertical(float AxisValue)
{
	FVector VerticalMovement = FVector::ForwardVector * AxisValue;
	if (VerticalMovement.Length() > 0.25f)
		AddMovementInput(VerticalMovement);
}

void APlayerCharacter::MoveHorizontal(float AxisValue)
{
	FVector HorizontalMovement = FVector::RightVector * AxisValue;
	if (HorizontalMovement.Length() > 0.25f)
		AddMovementInput(HorizontalMovement);
}


