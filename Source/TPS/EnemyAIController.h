// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "AIController.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();

	FTimerHandle ResetTimerHandler;

	virtual void Tick(float DeltaSeconds) override;

protected:

	APlayerCharacter* TargetedPlayer;

	virtual void BeginPlay() override;
};
