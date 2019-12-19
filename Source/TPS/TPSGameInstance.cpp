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

	ConstructorHelpers::FObjectFinder<UDataTable> EnemyTableFinder(
		TEXT("DataTable'/Game/TPS/DataTables/EnemyDataTable.EnemyDataTable'"));
	if (EnemyTableFinder.Succeeded())
	{
		DT_Enemy = EnemyTableFinder.Object;
		EnemyIdContainer = DT_Enemy->GetRowNames();
	}
}

/**********************************WeaponLoad****************************************/

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

// 포인터가 아닌 데이터가 복사된 경우 매개변수로 참조형으로 받음
// 장점: return값을 bool값으로 함으로써 받아올수 있는지 없는지 판단
bool UTPSGameInstance::FindWeaponPreset(const FName& InWeaponId, FWeaponPreset& OutPreset)
{
	FDataTableRowHandle WeaponRowHandle;

	WeaponRowHandle.DataTable = DT_Weapon;
	WeaponRowHandle.RowName = InWeaponId;

	FWeaponPreset* Row = WeaponRowHandle.GetRow<FWeaponPreset>(FString());

	if (Row != nullptr)
	{
		// 찾아낸 Row가 가리키는 구조체를 복사
		OutPreset = *Row;
		return true;
	}

	return false;
}

FName UTPSGameInstance::GetRandomWeaponId() const
{
	return WeaponIdContainer[FMath::RandRange(0, WeaponIdContainer.Num() - 1)];
}

FName UTPSGameInstance::GetWeaponId(int32 WeaponIdIndex) const
{
	FDataTableRowHandle WeaponRowHandle;
	WeaponRowHandle.DataTable = DT_Weapon;
	WeaponRowHandle.RowName = FName(*FString::Printf(TEXT("Weapon%d"), WeaponIdIndex));

	FWeaponPreset* Row = WeaponRowHandle.GetRow<FWeaponPreset>(FString());
	
	if (Row != nullptr)
		return WeaponRowHandle.RowName;

	return FName();
}

AAmmoInventory* UTPSGameInstance::GetAmmoInventory()
{
	UClass* AmmoInven = AAmmoInventory::StaticClass();
	AmmoInventory = GetWorld()->SpawnActor<AAmmoInventory>(AmmoInven);
	
	if (IsValid(AmmoInventory))
		return AmmoInventory;
	else
		return nullptr;
}

// RandomKey 생성
EWeaponKind UTPSGameInstance::GetRandomWeaponKind()
{
	uint8 FirstValue = static_cast<uint8>(EWeaponKind::Rifle);
	uint8 LastValue = static_cast<uint8>(EWeaponKind::Default) - 1;
	uint8 KeyRandomValue = FMath::RandRange(FirstValue, LastValue);

	return static_cast<EWeaponKind>(KeyRandomValue);
}

/**********************************MonsterLoad****************************************/

UDataTable* UTPSGameInstance::LoadEnemyTable()
{
	DT_Enemy = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/TPS/DataTables/EnemyDataTable.EnemyDataTable'"));

	if (DT_Enemy == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT(" 테이블 참조를 찾을 수 없습니다."));
		return nullptr;
	}
	
	return DT_Enemy;
}

bool UTPSGameInstance::FindEnemyPreset(const FName& InEnemyId, FEnemyPreset& OutPreset)
{
	FDataTableRowHandle EnemyRowHandle;
	
	EnemyRowHandle.DataTable = DT_Enemy;
	EnemyRowHandle.RowName = InEnemyId;

	FEnemyPreset* Row = EnemyRowHandle.GetRow<FEnemyPreset>(FString());
	
	if (Row != nullptr)
	{
		OutPreset = *Row;
		return true;
	}

	return false;
}
