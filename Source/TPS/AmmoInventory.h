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

	// 상호 참조때문에 넣어준 것
	AWeaponBase* Weapon;	

	UFUNCTION(BlueprintCallable)
	int32 GetMaxAmmo(int32 Slot);

	UFUNCTION(BlueprintCallable)
	int32 GetTotalAmmoAmount(int32 Slot);

	// 무기 타입에 따른 남은 탄환 갯수 반환
	UFUNCTION(BlueprintCallable)
	int32 GetAmmo(EWeaponKind WeaponKind) const;

	// 무기 종류에 따라 탄환을 추가
	UFUNCTION(BlueprintCallable)
	void AddAmmo(EWeaponKind WeaponKind, int32 AddAmmo);

	// 탄환을 소비하여 장전할 수 있는 탄환 수를 반환
	// MagazineCount보다 적은 탄환 수가 남아있다면 남은 만큼 반환
	UFUNCTION(BlueprintCallable)
	int32 ConsumeAmmo(EWeaponKind WeaponKind, int32 MagazineCount);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EWeaponKind, int32> MaxAmmo;

	// 탄창에 있는 총 갯수
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
