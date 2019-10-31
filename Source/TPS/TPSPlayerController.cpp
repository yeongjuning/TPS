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

void ATPSPlayerController::StopReload()
{
	IsPlaying();
	DoesPlayerExist();

	GetTPSPlayer()->StopReload();
}

void ATPSPlayerController::Attack()
{
	IsPlaying();
	DoesPlayerExist();

	UE_LOG(LogTemp, Log, TEXT("Attack"));

	GetAttackComponent()->bAttack = true;
}

void ATPSPlayerController::StopAttack()
{
	IsPlaying();
	DoesPlayerExist();

	UE_LOG(LogTemp, Log, TEXT("Stop Attack"));

	GetAttackComponent()->bAttack = false;
}

void ATPSPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// TODO :: CharacterStatus에 return 값이 bool값인 것으로 옮겨놓기
	if (GetCharStatus()->bCanThePlayerRun)
		GetCharStatus()->StaminaManager(GetTPSPlayer()->CurStamina, true);
	else
		GetCharStatus()->StaminaManager(GetTPSPlayer()->CurStamina, false);
	
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
	InputComponent->BindAction(TEXT("StopAttack"),
		EInputEvent::IE_Released, this, &ATPSPlayerController::StopAttack);

	InputComponent->BindAxis(TEXT("Move Forward"), this, &ATPSPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("Move Right"), this, &ATPSPlayerController::MoveRight);
}
