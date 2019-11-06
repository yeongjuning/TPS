// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/PlayerState.h"
#include "WeaponBase.h"

#include "AmmoInventory.generated.h"

class AWeaponBase;

/**
 * 
 */
UCLASS()
class TPS_API AAmmoInventory : public APlayerState
{
	GENERATED_BODY()

public:

	AAmmoInventory();

	// 상호 참조때문에 넣어준 것
	AWeaponBase* Weapon;	

	UFUNCTION(BlueprintCallable)
	float GetMaxAmmo();

	UFUNCTION(BlueprintCallable)
	float GetTotalAmmoAmount();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EWeaponKind, float> MaxAmmo;

	// 탄창에 있는 총 갯수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EWeaponKind, float> TotalAmmoAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxAmmoVal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TotalAmmoAmountVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAmmoEmpty = false;

protected:
	EWeaponKind MaxAmmoKey;
	EWeaponKind ToTalAmmoKey;
};
