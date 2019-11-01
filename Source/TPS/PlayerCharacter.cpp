// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("Camera Boom")));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->RelativeRotation = FRotator(-45.0f, 0.0f, 0.0f);
	CameraBoom->TargetArmLength = 1200.0f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 2.5f;
	CameraBoom->SetAbsolute(false, true, false);

	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("Main Camera")));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	ChildWeapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon Child Actor Component"));
	ChildWeapon->SetupAttachment(GetMesh());
}

void APlayerCharacter::Attack_Implementation()
{
	Super::Attack_Implementation();
}

void APlayerCharacter::StopAttack_Implementation()
{
	Super::StopAttack_Implementation();
}

void APlayerCharacter::Reload_Implementation()
{
	Super::Reload_Implementation();
}

void APlayerCharacter::StopReload_Implementation()
{
	Super::StopReload_Implementation();
}

void APlayerCharacter::Dead_Implementation()
{
	Super::Dead_Implementation();
}

void APlayerCharacter::ZoomToDeath()
{
	GetCameraBoom()->TargetArmLength = 1300.0f;
}

void APlayerCharacter::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void APlayerCharacter::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurStamina = GetStatus()->GetCurrentStamina();
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// 액터의 요를 회전하면, 붙어있는 카메라도 따라서 회전
	FRotator NewActorRotation = GetActorRotation();
	NewActorRotation.Yaw += CameraInput.X + DeltaSeconds * 10;
	SetActorRotation(NewActorRotation);

	// SpringArm의 Picth와 Yaw 회전
	FRotator NewRotation = CameraBoom->GetComponentRotation();
	NewRotation.Pitch += CameraInput.Y * DeltaSeconds * 10;
	NewRotation.Yaw += CameraInput.X * DeltaSeconds * 10;

	CameraBoom->SetWorldRotation(NewRotation);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("CameraPitch", this, &APlayerCharacter::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &APlayerCharacter::YawCamera);
}

