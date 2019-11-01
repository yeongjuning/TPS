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

	UFUNCTION(BlueprintCallable)
	void WeaponSpawn();

protected:

	UFUNCTION(BlueprintCallable)
	int32 GetWeaponSpawnPoint();

	UFUNCTION(BlueprintCallable)
	FTransform GetWeaponTransform();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon Class")
	TSubclassOf<AWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere, Category = "Game Instance")
	UTPSGameInstance* TPSGameInstance;

	UPROPERTY(VisibleAnywhere, Category = "Spawn Transform")
	int32 SpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Spawn Transform")
	FTransform SpawnTransform;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> WapSpawnPoints;

	UPROPERTY(VisibleAnywhere)
	AItemTrigger* ItemTrigger;

	FActorSpawnParameters Parameters;

	virtual void BeginPlay() override;

protected:

	UPROPERTY(VisibleAnywhere)
	EWeaponKind TableKey;

	UPROPERTY(VisibleAnywhere)
	AWeaponBase* Weapon;

	// Casting Destination
	UPROPERTY(VisibleAnywhere)
	UClass* WeaponActorClass;

};
