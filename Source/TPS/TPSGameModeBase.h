// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WeaponBase.h"
#include "AmmoInventory.h"
#include "WeaponSpawner.h"
#include "ItemTrigger.h"
#include "TPSGameInstance.h"
#include "TPSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API ATPSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATPSGameModeBase();

	UFUNCTION(BlueprintCallable)
	AItemTrigger* SpawnTrigger();

protected:

	UFUNCTION(BlueprintCallable)
	int32 GetWeaponSpawnPoint();

	UFUNCTION(BlueprintCallable)
	FTransform GetWeaponTransform();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Game Instance")
	UTPSGameInstance* TPSGameInstance;

	UPROPERTY(VisibleAnywhere, Category = "Spawn Transform")
	FTransform SpawnTransform;

	FActorSpawnParameters Parameters;

	UPROPERTY(VisibleAnywhere)
	TArray<AWeaponSpawner*> WapSpawnPoints;

	UPROPERTY(VisibleAnywhere)
	AItemTrigger* ItemTrigger;

	virtual void BeginPlay() override;

protected:

	UPROPERTY(VisibleAnywhere)
	EWeaponKind TableKey;

	UPROPERTY(VisibleAnywhere)
	AWeaponBase* Weapon;
};
