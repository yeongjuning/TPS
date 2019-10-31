// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameInstance.h"
#include "WeaponBase.h"

UTPSGameInstance::UTPSGameInstance()
{
}

// Table 가져오기
UDataTable* UTPSGameInstance::GetWeaponTable()
{
	DT_Weapon = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/TPS/DataTables/WeaponDataTable.WeaponDataTable'"));

	if (DT_Weapon == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("무기 테이블 참조를 찾을 수 없습니다."));
		return nullptr;
	}

	return DT_Weapon;
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

// EWeaponKind를 WeaponKey로 가져옴 -> 
EWeaponKind UTPSGameInstance::GetTableKey(FName RowName)
{
	EWeaponKind KeyValue = CreateRandomKey();

	for (TMap<EWeaponKind, FName>::TIterator It = WeaponTableMap.CreateIterator(); It; ++It)
	{
		KeyValue = It->Key;
		RowName = It->Value;
	}

	return KeyValue;
}

