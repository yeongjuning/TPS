// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameInstance.h"
#include "WeaponBase.h"


UTPSGameInstance::UTPSGameInstance()
{
	ConstructorHelpers::FObjectFinder<UDataTable> WeaponTableFinder(
		TEXT("DataTable'/Game/TPS/DataTables/WeaponDataTable.WeaponDataTable'"));
	if (WeaponTableFinder.Succeeded())
	{
		DT_Weapon = WeaponTableFinder.Object;
		WeaponIdContainer = DT_Weapon->GetRowNames();
	}
}

// Table 가져오기
UDataTable* UTPSGameInstance::LoadWeaponTable()
{
	DT_Weapon = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/TPS/DataTables/WeaponDataTable.WeaponDataTable'"));

	if (DT_Weapon == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("무기 테이블 참조를 찾을 수 없습니다."));
		return nullptr;
	}

	return DT_Weapon;
}

bool UTPSGameInstance::FindWeaponPreset(const FName& InWeaponId, FWeaponPreset* OutPreset)
{
	OutPreset = DT_Weapon->FindRow<FWeaponPreset>(InWeaponId, TEXT(""));
	return OutPreset != nullptr;
}

FName UTPSGameInstance::GetRandomWeaponId() const
{
	return WeaponIdContainer[FMath::RandRange(0, WeaponIdContainer.Num() - 1)];
}

void UTPSGameInstance::OnStart()
{
	Super::OnStart();
}

// RandomKey 생성
EWeaponKind UTPSGameInstance::GetRandomWeaponKind()
{
	uint8 FirstValue = static_cast<uint8>(EWeaponKind::Rifle);
	uint8 LastValue = static_cast<uint8>(EWeaponKind::Default) - 1;
	uint8 KeyRandomValue = FMath::RandRange(FirstValue, LastValue);

	return static_cast<EWeaponKind>(KeyRandomValue);
}