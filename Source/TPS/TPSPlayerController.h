// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "TPSGameState.h"
#include "CharacterStatus.h"
#include "AttackComponent.h"
#include "TPSCharacter.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"

#include "TPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API ATPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ATPSPlayerController();

	UFUNCTION()
	void DoesPlayerExist();
	
	UFUNCTION()
	void IsPlaying();

public:

	// TPS의 GameState 가져오기
	UFUNCTION(BlueprintCallable)
	ATPSGameState* GetTPSGameState() const { return Cast<ATPSGameState>(GetWorld()->GetGameState()); }

	// TPS의 Player 가져오기
	UFUNCTION(BlueprintCallable)
	APlayerCharacter* GetTPSPlayer() const { return Cast<APlayerCharacter>(GetCharacter()); }

	// Player의 Status 가져오기
	UFUNCTION(BlueprintCallable)
	UCharacterStatus* GetCharStatus() const { return Cast<UCharacterStatus>(GetTPSPlayer()->GetStatus()); }

	UFUNCTION(BlueprintCallable)
	UAttackComponent* GetAttackComponent() const { return Cast<UAttackComponent>(GetTPSPlayer()->GetAttackComponent()); }

protected:
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, BlueprintGetter = GetTPSGameState, Category = "Game State Manager")
	ATPSGameState* TPSGameState;

protected:

	UFUNCTION()
	void MoveForward(float AxisValue);

	UFUNCTION()
	void MoveRight(float AxisValue);

	UFUNCTION()
	void Run();

	UFUNCTION()
	void StopRun();

	UFUNCTION()
	void Reload();

	UFUNCTION()
	void CompleteReload();

	UFUNCTION()
	void Attack();

	UFUNCTION()
	void StopAttack();
protected:

	UFUNCTION(BlueprintCallable)
	void PullOutRifle();

	UFUNCTION(BlueprintCallable)
	void PullOutKnife();

	UFUNCTION(BlueprintCallable)
	void PullOutGrenade();

	UFUNCTION(BlueprintCallable)
	void ReapWeapon();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	FHitResult MouseHitResult;
	void RotValByMouseRot();

};

