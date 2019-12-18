// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "TPSGameModeBase.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("Camera Boom")));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->RelativeRotation = FRotator(-45.0f, 0.0f, 0.0f);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 2.5f;
	CameraBoom->SetAbsolute(false, true, false);

	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;

	CameraBoom->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("Main Camera")));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

void ATPSCharacter::EquipWeapon(int32 SlotIdx, AWeaponBase* WeaponActor)
{
	if (EquipedWeapons.IsValidIndex(SlotIdx) == false)
		return;

	if (IsValid(WeaponActor) == false)
		return;

	AttachWeaponActor(SlotIdx, WeaponActor);
	EquipedWeapons[SlotIdx] = WeaponActor;
}

void ATPSCharacter::PullOutWeapon(int32 SlotIdx, AWeaponBase* WeaponActor)
{
	if (EquipedWeapons.IsValidIndex(SlotIdx) == false)
		return;

	if (IsValid(WeaponActor) == false)
		return;
	
	FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

	WeaponActor->AttachToComponent(GetMesh(), AttachmentRule, TEXT("Socket_Hand_R"));
	SetCurrentWeaponSlot(SlotIdx);

	EquipedWeapons[SlotIdx]->Instigator = this;
	OnChangeCurrentWeapon.Broadcast(WeaponActor, SlotIdx);
}

void ATPSCharacter::DropWeapon(int32 SlotIdx)
{
	if (EquipedWeapons.IsValidIndex(SlotIdx) == false)
		return;

	Weapon = EquipedWeapons[SlotIdx];

	if (IsValid(Weapon))
		return;

	Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	UE_LOG(LogTemp, Log, TEXT("Slot Index : %d"), SlotIdx);

	EquipedWeapons[SlotIdx] = nullptr;

	CurrentWeaponSlot = -1;

	for (int32 i = 0; i < EquipedWeapons.Num(); i++)
	{
		if (IsValid(EquipedWeapons[i]))
		{
			CurrentWeaponSlot = i;
			UE_LOG(LogTemp, Log, TEXT("Drop Weapon : %d"), CurrentWeaponSlot);
			return;
		}
	}
}

void ATPSCharacter::AttachWeaponActor(int32 SlotIdx, AWeaponBase* WeaponActor)
{
	FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

	switch (SlotIdx)
	{
	case 0:
		WeaponActor->AttachToComponent(GetMesh(), AttachmentRule, TEXT("Rifle_Socket"));
		break;
	case 1:
		WeaponActor->AttachToComponent(GetMesh(), AttachmentRule, TEXT("Knife_Socket"));
		break;
	case 2:
		WeaponActor->AttachToComponent(GetMesh(), AttachmentRule, TEXT("Grenade_Socket"));
		break;
	default:
		break;
	}
}

void APlayerCharacter::Attack_Implementation()
{
	Super::Attack_Implementation();
}

void APlayerCharacter::Reload_Implementation()
{
	Super::Reload_Implementation();
}

void APlayerCharacter::Dead_Implementation()
{
	Super::Dead_Implementation();

	ZoomToDeath();
	Cast<ATPSGameState>(GetWorld()->GetGameState())->GamePlayingState = EGamePlayingState::GameOver;
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

