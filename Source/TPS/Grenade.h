// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "WeaponBase.h"
#include "Grenade.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API AGrenade : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AGrenade();

protected:

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
};
