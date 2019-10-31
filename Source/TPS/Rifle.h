// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "WeaponBase.h"
#include "AmmoInventory.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API ARifle : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ARifle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
};
