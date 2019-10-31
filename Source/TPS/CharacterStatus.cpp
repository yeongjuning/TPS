// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatus.h"

UCharacterStatus::UCharacterStatus()
{
	CurStamina = MaxStamina;
	CurHealth = MaxHealth;
}

// 달리는 중일 경우 Stamina 깎는 함수
void UCharacterStatus::StaminaManager(float& CurStamina, bool IsRunning)
{
	if (CurStamina < MaxStamina && !IsRunning)
	{
		CurStamina += 0.5f;
	}

	if (IsRunning)
	{
		bCanThePlayerRun = true;
		CurStamina -= 0.5f;

		if (CurStamina <= 0.0f)
		{
			CurStamina = 0.0f;
			bCanThePlayerRun = false;
		}
	}
}

float UCharacterStatus::HealthManager(float DamageAmount, float& CurrentHP)
{
	if (DamageAmount >= CurrentHP)
	{
		CurrentHP = 0.0f;
	}
	else
		CurrentHP -= DamageAmount;

	return CurrentHP;
}



