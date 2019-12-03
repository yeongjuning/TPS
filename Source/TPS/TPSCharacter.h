// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "TPSGameState.h"
#include "CharacterStatus.h"

#include "TPSCharacter.generated.h"

class AWeaponBase;
class UAttackComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponChangeSignature, AWeaponBase*, ChangedWeapon, int32, SlotIndex);

UCLASS()
class TPS_API ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	static const int32 MaxWeaponSlot;

	// 무기가 변경될때 호출되는 이벤트 델리게이트
	UPROPERTY(BlueprintAssignable)
	FWeaponChangeSignature OnChangeCurrentWeapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AWeaponBase* Weapon;

public:
	// Sets default values for this character's properties
	ATPSCharacter();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(int32 SlotIdx, AWeaponBase* WeaponActor);

	UFUNCTION(BlueprintCallable)
	void DropWeapon(int32 SlotIdx);

public:	// Weapon의 Slot과 관련된 함수 

	UFUNCTION(BlueprintCallable)
	void SetCurrentWeaponSlot(int32 SlotIdx);

	// 슬롯 번호에 장착된 무기 참조를 반환
	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetWeapon(int32 SlotIdx) const;

	// 현재 사용중인 무기 슬롯 번호를 반환
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentWeaponSlot() const { return CurrentWeaponSlot; }

	// 현재 사용중인 무기 참조 반환
	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetCurrentWeapon() const;

	// 현재 장착된 무기의 공격속도를 반환
	UFUNCTION(BlueprintCallable)
	float GetAttackSpeed() const;

public:

	// 그냥 행동만 보여주기 위한 함수
	// 실질적인 행동은 AttackComponent에서 실행
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Attack();
	virtual void Attack_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reload();
	virtual void Reload_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CompleteReload();
	virtual void CompleteReload_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Dead();
	virtual void Dead_Implementation();

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float CurHP = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float CurStamina = 0.0f;

public:

	UFUNCTION(BlueprintCallable)
	UAttackComponent* GetAttackComponent() const { return AttackComponent; }

	UFUNCTION(BlueprintCallable)
	UCharacterStatus* GetStatus() const { return CharStatus; }

public:

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return bIsDead; }

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintGetter = IsDead, Category = "Possible Behavior")
	bool bIsDead = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual float TakeDamage(
		float DamageAmount,
		FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

	/*void HealthOfDamage(float DamageAmount, float& CharacterHealth);*/

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	FTimerHandle DeathTimerHandler;
	UFUNCTION()
	void OnDeathTimerComplete();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), BlueprintGetter = GetStatus)
	UCharacterStatus* CharStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), BlueprintGetter = GetAttackComponent)
	UAttackComponent* AttackComponent;

private:

	UPROPERTY(VisibleAnywhere, SaveGame)
	TArray<AWeaponBase*> EquipedWeapons;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintGetter = GetCurrentWeaponSlot)
	int32 CurrentWeaponSlot = 0;
};
