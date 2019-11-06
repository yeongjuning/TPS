// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TargetedPlayer = Cast<APlayerCharacter>(GetBlackboardComponent()->GetValueAsObject(TEXT("TargetToFollow")));

	if (TargetedPlayer == nullptr)
		return;

	if (TargetedPlayer->IsDead())
	{
		// 시간 초기화
		GetWorldTimerManager().ClearTimer(ResetTimerHandler);

		GetBlackboardComponent()->SetValueAsBool(TEXT("HasLineOfSight"), false);
		GetBlackboardComponent()->SetValueAsObject(TEXT("TargetToFollow"), nullptr);
		GetBlackboardComponent()->SetValueAsBool(TEXT("IsDead"), true);
	}
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}
