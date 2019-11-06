// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyCharacter::Dead_Implementation()
{
	Super::Dead_Implementation();
	// TODO :: ��� ī���� �� ���Ͱ� �׾���� GameState�� Clear
	Cast<ATPSGameState>(GetWorld()->GetGameState())->GamePlayingState = EGamePlayingState::Clear;
}

void AEnemyCharacter::Attack_Implementation()
{
	Super::Attack_Implementation();
}

void AEnemyCharacter::StopAttack_Implementation()
{
	Super::StopAttack_Implementation();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}
