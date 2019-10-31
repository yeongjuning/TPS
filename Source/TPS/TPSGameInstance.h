// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine/GameInstance.h"
#include "TPSGameState.h"
#include "PlayerCharacter.h"
#include "CharacterStatus.h"
#include "Engine/DataTable.h"
#include "AmmoInventory.h"
#include "WeaponBase.h"

#include "TPSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UTPSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	EWeaponKind GetTableKeys(FName RowName);

	UFUNCTION(BlueprintCallable)
	void SetWeaponPreset(EWeaponKind WeapTableKey);

public:
	UTPSGameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	ATPSGameState* TPSGameState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Status")
	UCharacterStatus* CharacterStatus;

public:

	FWeaponPreset* WeaponPreset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info")
	UDataTable* WeaponDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Info")
	TMap<EWeaponKind, FName> TableKeys;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Info")
	TSoftClassPtr<AWeaponBase> WeaponAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo Inventory")
	AAmmoInventory* AmmoInven;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Map Key")
	EWeaponKind NewKeyValue;

private:

	UFUNCTION()
	EWeaponKind CreateRandomKey();
};
