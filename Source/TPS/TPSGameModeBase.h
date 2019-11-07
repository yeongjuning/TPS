// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WeaponBase.h"
#include "AmmoInventory.h"
#include "WeaponSpawner.h"
#include "ItemTrigger.h"
#include "TPSGameInstance.h"
#include "EnemySpawner.h"
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

protected:

	UFUNCTION(BlueprintCallable)
	int32 GetRandomWeaponSpawnPoint() const;

	UFUNCTION(BlueprintCallable)
	FTransform GetRandomWeaponTransform();

	UFUNCTION(BlueprintCallable)
	void SpawnTrigger();

protected:

	UFUNCTION(BlueprintCallable)
	int32 GetRandomEnemySpawnPoint() const;

	UFUNCTION(BlueprintCallable)
	FTransform GetRandomEnemyTransform();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon Class")
	TSubclassOf<AWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere, Category = "Game Instance")
	UTPSGameInstance* TPSGameInstance;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Weapon Spawn Transform")
	int32 WapSpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Spawn Transform")
	FTransform RandomWapSpawnTransform;

	UPROPERTY(VisibleAnywhere)
	AItemTrigger* ItemTrigger;


protected:

	UPROPERTY(VisibleAnywhere, Category = "Enemy Spawn Transform")
	int32 EnemySpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = "Enemy Spawn Transform")
	FTransform RandomEnemySpawnTransform;

protected:

	UPROPERTY(VisibleAnywhere)
	AWeaponBase* Weapon;

	virtual void BeginPlay() override;
private:

	FActorSpawnParameters Parameters;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> WapSpawnPoints;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> EnemySpawnPoints;
};
