// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "WeaponBase.h"
#include "AmmoInventory.h"
#include "Knife.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API AKnife : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AKnife();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void FireAndAttack_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual void StopFireAndAttack_Implementation() override;

public:
	virtual void Tick(float DeltaSeconds) override;
};
