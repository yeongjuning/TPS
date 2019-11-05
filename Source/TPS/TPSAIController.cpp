// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSAIController.h"

ATPSAIController::ATPSAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATPSAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void ATPSAIController::BeginPlay()
{
	Super::BeginPlay();
}