// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine/GameInstance.h"
#include "TPSGameState.h"
#include "TPSCharacter.h"
#include "PlayerCharacter.h"
#include "CharacterStatus.h"
#include "EnemyCharacter.h"
#include "Engine/DataTable.h"
#include "AmmoInventory.h"

#include "TPSGameInstance.generated.h"

class AWeaponBase;
struct FWeaponPreset;

UCLASS()
class TPS_API UTPSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UTPSGameInstance();

	UFUNCTION(BlueprintCallable)
	UDataTable* LoadWeaponTable();

	UFUNCTION(BlueprintCallable)
	bool FindWeaponPreset(const FName& InWeaponId, FWeaponPreset& OutPreset);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetRandomWeaponId() const;	

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetWeaponId(int32 WeaponIdIndex) const;

	UFUNCTION(BlueprintCallable)
	AAmmoInventory* GetAmmoInventory();

public:
	
	UFUNCTION(BlueprintCallable)
	UDataTable* LoadEnemyTable();

	UFUNCTION(BlueprintCallable)
	bool FindEnemyPreset(const FName& InEnemyId, FEnemyPreset& OutPreset);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	ATPSGameState* TPSGameState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ATPSCharacter* TPSCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Status")
	UCharacterStatus* CharacterStatus;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Inventory")
	AAmmoInventory* AmmoInventory;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Table")
	UDataTable* DT_Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Table")
	UDataTable* DT_Enemy;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponKind WeaponMapKey;

private:

	UFUNCTION()
	EWeaponKind GetRandomWeaponKind();

	TArray<FName> WeaponIdContainer;
	TArray<FName> EnemyIdContainer;
};
