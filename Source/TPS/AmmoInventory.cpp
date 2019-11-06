// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoInventory.h"
#include "WeaponBase.h"

AAmmoInventory::AAmmoInventory()
{
	PrimaryActorTick.bCanEverTick = true;
}

float AAmmoInventory::GetMaxAmmo()
{
	MaxAmmo.Add(EWeaponKind::Rifle, 30.0f);
	MaxAmmo.Add(EWeaponKind::Knife, 1.0f);
	MaxAmmo.Add(EWeaponKind::Grenade, 3.0f);

	for (TMap<EWeaponKind, float>::TIterator it = MaxAmmo.CreateIterator(); it; ++it)
	{
		MaxAmmoKey = it->Key;
		MaxAmmoVal = it->Value;
	}

	return MaxAmmoVal;
}

float AAmmoInventory::GetTotalAmmoAmount()
{
	TotalAmmoAmount.Add(EWeaponKind::Rifle, 150.0f);
	TotalAmmoAmount.Add(EWeaponKind::Knife, 1.0f);
	TotalAmmoAmount.Add(EWeaponKind::Grenade, 3.0f);

	for (TMap<EWeaponKind, float>::TIterator it = TotalAmmoAmount.CreateIterator(); it; ++it)
	{
		ToTalAmmoKey = it->Key;
		TotalAmmoAmountVal = it->Value;
	}

	return TotalAmmoAmountVal;
}

//// todo:: 각 무기 액터로 옮기기
//TMap<EWeaponKind, int32> AAmmoInventory::GetMagazineCount()
//{
//	MagazineCount.Add(EWeaponKind::Rifle, 5.0f);
//	MagazineCount.Add(EWeaponKind::Knife, 1.0f);
//	MagazineCount.Add(EWeaponKind::Grenade, 0.0f);
//
//	for (TMap<EWeaponKind, int32>::TIterator it = MagazineCount.CreateIterator(); it; ++it)
//	{
//		EWeaponKind Key = it->Key;
//		float MagazineCountVal = it->Value;
//	}
//
//	return MagazineCount;
//}

//// todo :: Rifle에 그냥 넣어주기
//TMap<EWeaponKind, float> AAmmoInventory::GetConsumeAmount()
//{
//	ConsumeAmount.Add(EWeaponKind::Rifle, 1.0f);
//	ConsumeAmount.Add(EWeaponKind::Knife, 0.0f);
//	ConsumeAmount.Add(EWeaponKind::Grenade, 1.0f);
//
//	for (TMap<EWeaponKind, float>::TIterator it = ConsumeAmount.CreateIterator(); it; ++it)
//	{
//		EWeaponKind Key = it->Key;
//		float ConsumeAmount = it->Value;
//	}
//
//	return ConsumeAmount;
//}



