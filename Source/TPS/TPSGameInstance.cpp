// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameInstance.h"

UTPSGameInstance::UTPSGameInstance()
{
	// 게임의 정보들
	// 무기테이블등을 멤버 변수로 둬주기
}

// RandomKey생성
EWeaponKind UTPSGameInstance::CreateRandomKey()
{
	uint8 FirstValue = static_cast<uint8>(EWeaponKind::Rifle);
	uint8 LastValue = static_cast<uint8>(EWeaponKind::Default) - 1;
	uint8 KeyRandomValue = FMath::RandRange(FirstValue, LastValue);

	NewKeyValue = static_cast<EWeaponKind>(KeyRandomValue);

	return NewKeyValue;
}

// TODO :: RowName을 통해서 얻은 키값을 토대로 GameMode에서 Asset을 Load 해주기
EWeaponKind UTPSGameInstance::GetTableKeys(FName RowName)
{
	EWeaponKind KeyValue = CreateRandomKey();

	for (TMap<EWeaponKind, FName>::TIterator It = TableKeys.CreateIterator(); It; ++It)
	{
		KeyValue = It->Key;
		RowName = It->Value;
	}

	return KeyValue;
}



void UTPSGameInstance::SetWeaponPreset(EWeaponKind WeapTableKey)
{
	UClass* WeaponBaseClass = WeaponPreset->WeaponAsset.LoadSynchronous();
}
