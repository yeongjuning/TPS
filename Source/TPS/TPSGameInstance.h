// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine/GameInstance.h"
#include "TPSGameState.h"
#include "PlayerCharacter.h"
#include "CharacterStatus.h"
#include "Engine/DataTable.h"
#include "AmmoInventory.h"

#include "TPSGameInstance.generated.h"

struct FWeaponPreset;
class AWeaponBase;

UCLASS()
class TPS_API UTPSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UTPSGameInstance();

	UFUNCTION(BlueprintCallable)
	UDataTable* LoadWeaponTable();

	bool FindWeaponPreset(const FName& InWeaponId, FWeaponPreset* OutPreset);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetRandomWeaponId() const;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game State")
	ATPSGameState* TPSGameState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Status")
	UCharacterStatus* CharacterStatus;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info")
	UDataTable* DT_Weapon;

protected:
	virtual void OnStart() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWeaponKind WeaponMapKey;

private:

	UFUNCTION()
	EWeaponKind GetRandomWeaponKind();

	TArray<FName> WeaponIdContainer;
};
