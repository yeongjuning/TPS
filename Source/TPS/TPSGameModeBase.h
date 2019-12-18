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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SpawnIndex = 0;

public:

	TArray<FTransform> RandTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AWeaponBase*> Weapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FName> CurSpawnedWeaponIds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AItemTrigger*> Triggers;

public:	// Weapon

	// Spawn할 Random 갯수 가져오는 함수
	UFUNCTION(BlueprintCallable)
	int32 GetRandomWeaponSpawnCount();

	// 월드에 배치된 WeaponSpawner중에 Random으로 생성될 Point를 얻는 함수
	UFUNCTION(BlueprintCallable)
	FTransform GetRandomWeaponSpawnPoint();

	// Trigger를 Spawn할 함수
	UFUNCTION(BlueprintCallable)
	void RandomTriggerSpawn(int32 InputIndex, FTransform InputTransform);

	// WeaponActor의 값을 DataTable에서 받아 Random으로 Spawn하는 함수
	UFUNCTION(BlueprintCallable)
	void RandomWeaponSpawn();

	// 랜덤으로 책정된 Count수 만큼 Spawn됬을 때, 같은 Transform인지 확인하는 함수
	UFUNCTION(BlueprintCallable)
	bool CheckEqulRandomTransform(int32 TransIdx, int32 Count) const;
	
public:

	// 현재 Spawn된 Weapon의 Id를 Set 해주는 Setter 함수
	UFUNCTION(BlueprintCallable)
	void SetCurrentSpawnedIdIndex(int32 WeaponIdIndex);

	// Index를 통한 Spawned된 Weapon의 Id를 찾는 Gettter 함수
	UFUNCTION(BlueprintCallable)
	FName GetSpawnedId(int32 WeaponIdIndex) const;

	// 현재의 인덱스(CurrentSpawendIndex) 를 통해서 SpawnedId를 찾는 함수
	UFUNCTION(BlueprintCallable)
	FName GetCurrentSpawnedId() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentSpawnedIndex() const { return CurrentSpawnedIndex; }

public:	// Enemy

	UFUNCTION(BlueprintCallable)
	int32 GetRandomEnemySpawnPoint() const;

	UFUNCTION(BlueprintCallable)
	FTransform GetRandomEnemyTransform();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

public:
	FTimerHandle WeaponSpawnTimeHandle;

	UFUNCTION()
	void VisibleTimer();

protected:

	UFUNCTION(BlueprintCallable)
	void WeaponsSpawn(int32 TriggerIdx, FName SpawnId, FWeaponPreset Preset);

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

	virtual void BeginPlay() override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Game Instance")
	UTPSGameInstance* TPSGameInstance;

	UPROPERTY(VisibleAnywhere, Category = "Trigger")
	UClass* TriggerClass;

private:

	FWeaponPreset WeaponPreset;

	FActorSpawnParameters Parameters;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> WapSpawnPoints;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> EnemySpawnPoints;

	UPROPERTY(VisibleAnywhere, BlueprintGetter = GetCurrentSpawnedIndex)
	int32 CurrentSpawnedIndex = 0;

	// Spawn에 필요한 모든 배열들의 동적인 길이를 Setting하는 함수
	UFUNCTION(BlueprintCallable)
	void SetArrRelatedToWeaponSpawn(int32 ArrLength);

};
