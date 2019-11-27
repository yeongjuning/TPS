// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponBase.h"
#include "AmmoInventory.h"

#include "AttackComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponChangeSignature, AWeaponBase*, ChangedWeapon, int32, SlotIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReloadSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_API UAttackComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	static const int32 MaxWeaponSlot;

	// 무기가 변경될때 호출되는 이벤트 델리게이트
	UPROPERTY(BlueprintAssignable)
	FWeaponChangeSignature OnChangeCurrentWeapon;

	UPROPERTY(BlueprintAssignable)
	FReloadSignature OnStartReload;

	UPROPERTY(BlueprintAssignable)
	FReloadSignature OnCompleteReload;

	// 무기가 변경될 때 마다 변경될 애니매이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TMap<EWeaponKind, TSubclassOf<UAnimInstance>> WeaponAnimClasses;

public:

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(int32 SlotIdx, AWeaponBase* WeaponActor);

	UFUNCTION(BlueprintCallable)
	void DropWeapon(int32 SlotIdx);

	UFUNCTION(BlueprintCallable)
	void SetCurrentWeaponSlot(int32 SlotIdx);

	// 슬롯 번호에 장착된 무기 참조를 반환
	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetWeapon(int32 SlotIdx) const;

	// 현재 장착된 무기의 공격속도를 반환
	UFUNCTION(BlueprintCallable)
	float GetAttackSpeed() const;

	// 현재 사용중인 무기 슬롯 번호를 반환
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentWeaponSlot() const { return CurrentWeaponSlot; }

	// 현재 사용중인 무기 참조 반환
	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetCurrentWeapon() const;

	// 현재 들고 있는 무기를 재장전
	UFUNCTION(BlueprintCallable)
	void StartReload();

	// 재장전이 완료되면 호출
	UFUNCTION(BlueprintCallable)
	void CompleteReload();

	// 무기가 있는지 판단한 후 Attack
	UFUNCTION(BlueprintCallable)
	void Attacking();

public:

	UFUNCTION(BlueprintCallable)
	void Attack();	

	UFUNCTION(BlueprintCallable)
	void StopAttack();

public:	
	// Sets default values for this component's properties
	UAttackComponent();

	UFUNCTION(BlueprintCallable)
	bool IsAttacking() const { return bCanAttack; }

	UFUNCTION(BlueprintCallable)
	bool IsReloading() const { return bReloading; }

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	//UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly)
	//bool bCanAttack = false;

	FTimerHandle WaitAttackTimer;

	void OnWaitAttackTimerEnd();

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, SaveGame)
	TArray<AWeaponBase*> EquipedWeapons;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintGetter = GetCurrentWeaponSlot)
	int32 CurrentWeaponSlot = 0;

	UPROPERTY(VisibleAnywhere, BlueprintGetter = IsAttacking)
	bool bCanAttack = false;

	UPROPERTY(VisibleAnywhere, BlueprintGetter = IsReloading)
	bool bReloading = false;
};
