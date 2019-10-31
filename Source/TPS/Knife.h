// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "WeaponBase.h"
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

public:
	virtual void Tick(float DeltaSeconds) override;
};
