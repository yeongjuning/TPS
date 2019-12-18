// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "TPSPlayerController.h"

ATPSPlayerController::ATPSPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;

	SetupInputComponent();
}

void ATPSPlayerController::IsPlaying()
{
	if (GetTPSGameState()->GamePlayingState != EGamePlayingState::Playing)
		UE_LOG(LogTemp, Log, TEXT("Currently not in Play"));
		return;
}

void ATPSPlayerController::DoesPlayerExist()
{
	if (GetTPSPlayer() == nullptr)
		UE_LOG(LogTemp, Log, TEXT("Player is null"));
		return;
}

void ATPSPlayerController::MoveForward(float AxisValue)
{
	IsPlaying();
	DoesPlayerExist();

	GetTPSPlayer()
		->GetCharacterMovement()
		->AddInputVector(FVector::ForwardVector * AxisValue);
}

void ATPSPlayerController::MoveRight(float AxisValue)
{
	IsPlaying();
	DoesPlayerExist();

	GetTPSPlayer()
		->GetCharacterMovement()
		->AddInputVector(FVector::RightVector * AxisValue);
}

void ATPSPlayerController::Run()
{
	IsPlaying();
	DoesPlayerExist();

	GetCharStatus()->bCanThePlayerRun = true;
	GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ATPSPlayerController::StopRun()
{
	IsPlaying();
	DoesPlayerExist();

	GetCharStatus()->bCanThePlayerRun = false;
	GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ATPSPlayerController::Reload()
{
	IsPlaying();
	DoesPlayerExist();

	GetTPSPlayer()->Reload();
}

void ATPSPlayerController::CompleteReload()
{
	IsPlaying();
	DoesPlayerExist();

	GetTPSPlayer()->CompleteReload();
}

void ATPSPlayerController::Attack()
{
	IsPlaying();
	DoesPlayerExist();

	GetTPSPlayer()->Attack();
}

//void ATPSPlayerController::StopAttack()
//{
//	IsPlaying();
//	DoesPlayerExist();
//
//	UE_LOG(LogTemp, Log, TEXT("Stop Attack"));
//
//	GetAttackComponent()->bAttack = false;
//}

void ATPSPlayerController::PullOutRifle()
{
	IsPlaying();
	DoesPlayerExist();

	AWeaponBase* Rilfe = GetTPSPlayer()->GetWeapon(0);

	if (IsValid(Rilfe) == false)
		return;

	UE_LOG(LogTemp, Log, TEXT("Pull Out Rifle"));
	GetTPSPlayer()->SetCurrentWeaponSlot(0);
	GetTPSPlayer()->PullOutWeapon(0, Rilfe);
}

void ATPSPlayerController::PullOutKnife()
{
	IsPlaying();
	DoesPlayerExist();

	AWeaponBase* Knife = GetTPSPlayer()->GetWeapon(1);

	if (IsValid(Knife) == false)
		return;

	UE_LOG(LogTemp, Log, TEXT("Pull Out Knife"));
	GetTPSPlayer()->SetCurrentWeaponSlot(1);
	GetTPSPlayer()->PullOutWeapon(0, Knife);
}

void ATPSPlayerController::PullOutGrenade()
{
	IsPlaying();
	DoesPlayerExist();

	AWeaponBase* Grenade = GetTPSPlayer()->GetWeapon(2);

	if (IsValid(Grenade) == false)
		return;
	
	UE_LOG(LogTemp, Log, TEXT("Pull Out Grenade"));
	GetTPSPlayer()->SetCurrentWeaponSlot(2);
	GetTPSPlayer()->PullOutWeapon(0, Grenade);
}

void ATPSPlayerController::ReapWeapon()
{
	IsPlaying();
	DoesPlayerExist();

	AWeaponBase* CurrentWeapon = GetTPSPlayer()->GetCurrentWeapon();

	if (IsValid(CurrentWeapon) == false)
		return;

	GetTPSPlayer()->AttachWeaponActor(GetTPSPlayer()->GetCurrentWeaponSlot(), CurrentWeapon);

	UE_LOG(LogTemp, Log, TEXT("Readp Weapon"));
}

void ATPSPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetCharStatus()->bCanThePlayerRun)
		GetCharStatus()->StaminaManager(GetTPSPlayer()->CurStamina);
	else
		GetCharStatus()->StaminaManager(GetTPSPlayer()->CurStamina);

	RotValByMouseRot();
}

void ATPSPlayerController::RotValByMouseRot()
{
	if (GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility), false, MouseHitResult))
	{
		IsPlaying();
		DoesPlayerExist();

		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetCharacter()->GetActorLocation(), MouseHitResult.Location);
		FRotator OldRotation = GetCharacter()->GetActorRotation();

		NewRotation.Pitch = OldRotation.Pitch;
		NewRotation.Roll = OldRotation.Roll;

		GetCharacter()->SetActorRotation(NewRotation);
	}
}

void ATPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InputComponent->BindAction(TEXT("Reload"),
		EInputEvent::IE_Pressed, this, &ATPSPlayerController::Reload);

	InputComponent->BindAction(TEXT("Run"),
		EInputEvent::IE_Pressed, this, &ATPSPlayerController::Run);
	InputComponent->BindAction(TEXT("StopRun"),
		EInputEvent::IE_Released, this, &ATPSPlayerController::StopRun);

	InputComponent->BindAction(TEXT("Attack"),
		EInputEvent::IE_Pressed, this, &ATPSPlayerController::Attack);
	//InputComponent->BindAction(TEXT("StopAttack"),
	//	EInputEvent::IE_Released, this, &ATPSPlayerController::StopAttack);

	InputComponent->BindAction(TEXT("PullOutRifle"),
		EInputEvent::IE_Pressed, this, &ATPSPlayerController::PullOutRifle);

	InputComponent->BindAction(TEXT("PullOutKnife"),
		EInputEvent::IE_Pressed, this, &ATPSPlayerController::PullOutKnife);

	InputComponent->BindAction(TEXT("PullOutGreande"),
		EInputEvent::IE_Pressed, this, &ATPSPlayerController::PullOutGrenade);

	InputComponent->BindAction(TEXT("ReapWeapon"),
		EInputEvent::IE_Pressed, this, &ATPSPlayerController::ReapWeapon);

	InputComponent->BindAxis(TEXT("Move Forward"), this, &ATPSPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("Move Right"), this, &ATPSPlayerController::MoveRight);
}
