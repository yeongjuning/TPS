// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterStatus.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UCharacterStatus : public UObject
{
	GENERATED_BODY()

public:
	UCharacterStatus();

	UFUNCTION()
	void StaminaManager(float& CurStamina, bool IsRunning);

	UFUNCTION()
	float HealthManager(float DamageAmount, float& CurrentHP);

public:
	// Get Stamina Info
	//UFUNCTION(BlueprintCallable)
	//FORCEINLINE bool IsStaminaZero() const { return CurStamina <= 0.0f; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCurrentStamina() const { return CurStamina; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool CanThePlayerRun() const { return bCanThePlayerRun; }

public:
	// Get Health Info
	UFUNCTION(BlueprintCallable)
	bool IsHealthZero() const { return CurHealth <= 0.0f; }

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const { return CurHealth; }

	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintGetter = IsHealthZero, Category = "Health")
	bool bIsHealthZero = false;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintGetter = IsStaminaZero, Category = "Stamina")
	//bool bIsStaminaZero = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter = CanThePlayerRun, Category = "Stamina")
	bool bCanThePlayerRun = false;

protected:

	// Stamina
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetMaxStamina, Category = "Stamina")
	float MaxStamina = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetCurrentStamina, Category = "Stamina")
	float CurStamina = 0.0f;
	
	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetMaxHealth, Category = "Health")
	float MaxHealth = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintGetter = GetCurrentHealth, Category = "Health")
	float CurHealth = 0.0f;
};
