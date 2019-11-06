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

	// ��ȣ ���������� �־��� ��
	AWeaponBase* Weapon;	

	UFUNCTION(BlueprintCallable)
	float GetMaxAmmo();

	UFUNCTION(BlueprintCallable)
	float GetTotalAmmoAmount();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EWeaponKind, float> MaxAmmo;

	// źâ�� �ִ� �� ����
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
