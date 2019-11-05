// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "AIController.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "TPSAIController.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API ATPSAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATPSAIController();

	FTimerHandle ResetTimerHandler;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	APlayerCharacter* TargetedPlayer;
};
