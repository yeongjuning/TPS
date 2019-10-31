// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TPSGameState.generated.h"

UENUM(BlueprintType)
enum class EGamePlayingState : uint8
{
	Playing,
	GameOver,
	Clear
};
/**
 * 
 */
UCLASS()
class TPS_API ATPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ATPSGameState();

	UFUNCTION()
	void ChangeOfState();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EGamePlayingState GamePlayingState = EGamePlayingState::Playing;
};
