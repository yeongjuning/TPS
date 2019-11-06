// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "TPSGameState.h"
#include "CharacterStatus.h"
#include "AttackComponent.h"

#include "TPSCharacter.generated.h"

class AWeaponBase;

UCLASS()
class TPS_API ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintGetter = GetWeapon)
	AWeaponBase* Weapon;

public:
	// Sets default values for this character's properties
	ATPSCharacter();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Attack();
	virtual void Attack_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopAttack();
	virtual void StopAttack_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reload();
	virtual void Reload_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopReload();
	virtual void StopReload_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Dead();
	virtual void Dead_Implementation();

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float CurHP = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float CurStamina = 0.0f;

	UFUNCTION(BlueprintCallable)
	UAttackComponent* GetAttackComponent() const { return AttackComponent; }

	UFUNCTION(BlueprintCallable)
	UCharacterStatus* GetStatus() const { return CharStatus; }

	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetWeapon() const { return Weapon; }

public:

	UFUNCTION(BlueprintCallable)
	bool IsReload() const { return bIsReload; }

	UFUNCTION(BlueprintCallable)
	bool IsStopReload() const { return !bIsReload; }

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return bIsDead; }

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintGetter = IsReload, Category = "Possible Behavior")
	bool bIsReload = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintGetter = IsDead, Category = "Possible Behavior")
	bool bIsDead = false;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	FTimerHandle ReloadTimerHandler;
	UFUNCTION()
	void OnReloadTimerComplete();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), BlueprintGetter = GetStatus)
	UCharacterStatus* CharStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), BlueprintGetter = GetAttackComponent)
	UAttackComponent* AttackComponent;
};
