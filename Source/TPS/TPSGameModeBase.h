// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WeaponBase.h"
#include "AmmoInventory.h"
#include "WeaponSpawner.h"
#include "TPSGameInstance.h"
#include "EnemySpawner.h"

#include "TPSGameModeBase.generated.h"

class AItemTrigger;
/**
 * 
 */
UCLASS()
class TPS_API ATPSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATPSGameModeBase();

	FORCEINLINE AItemTrigger* GetSpawnedTrigger() const { return SpawnedTrigger; }
	FORCEINLINE FTransform GetWeaponTransform() const { return WeaponTransform; }

public:	// Weapon

	UFUNCTION(BlueprintCallable)
	int32 GetRandomWeaponSpawnPoint() const;

	UFUNCTION(BlueprintCallable)
	int32 GetRandomWeaponSpawnCount();

	UFUNCTION(BlueprintCallable)
	FTransform GetRandomWeaponTransform();

	UFUNCTION(BlueprintCallable)
	void SpawnTrigger();

public:	// Enemy

	UFUNCTION(BlueprintCallable)
	int32 GetRandomEnemySpawnPoint() const;

	UFUNCTION(BlueprintCallable)
	FTransform GetRandomEnemyTransform();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Game Instance")
	UTPSGameInstance* TPSGameInstance;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Weapon Spawn Transform")
	int32 WapSpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Spawn Transform")
	FTransform RandomWapSpawnTransform;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Enemy Spawn Transform")
	int32 EnemySpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Enemy Spawn Transform")
	FTransform RandomEnemySpawnTransform;

	UPROPERTY(VisibleAnywhere)
	AItemTrigger* SpawnedTrigger;

	virtual void BeginPlay() override;

private:

	FWeaponPreset Preset;

	FActorSpawnParameters Parameters;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> WapSpawnPoints;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> EnemySpawnPoints;

	FTransform WeaponTransform;
};
