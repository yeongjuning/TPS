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

	UPROPERTY(VisibleAnywhere, SaveGame)
	TMap<EWeaponKind, int32> AmmoInventory;

public:

	AAmmoInventory();

	// ��ȣ ���������� �־��� ��
	AWeaponBase* Weapon;	

	UFUNCTION(BlueprintCallable)
	int32 GetMaxAmmo(int32 Slot);

	UFUNCTION(BlueprintCallable)
	int32 GetTotalAmmoAmount(int32 Slot);

	// ���� Ÿ�Կ� ���� ���� źȯ ���� ��ȯ
	UFUNCTION(BlueprintCallable)
	int32 GetAmmo(EWeaponKind WeaponKind) const;

	// ���� ������ ���� źȯ�� �߰�
	UFUNCTION(BlueprintCallable)
	void AddAmmo(EWeaponKind WeaponKind, int32 AddAmmo);

	// źȯ�� �Һ��Ͽ� ������ �� �ִ� źȯ ���� ��ȯ
	// MagazineCount���� ���� źȯ ���� �����ִٸ� ���� ��ŭ ��ȯ
	UFUNCTION(BlueprintCallable)
	int32 ConsumeAmmo(EWeaponKind WeaponKind, int32 MagazineCount);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EWeaponKind, int32> MaxAmmo;

	// źâ�� �ִ� �� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EWeaponKind, int32> TotalAmmoAmount;

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
