// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "AmmoInventory.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Table 가져오기
UDataTable* AWeaponBase::GetWeaponTable()
{
	DT_Weapon = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/TPS/DataTables/WeaponDataTable.WeaponDataTable'"));
	
	if (DT_Weapon == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("무기 테이블 참조를 찾을 수 없습니다."));
		return nullptr;
	}
	
	return DT_Weapon;
}

// RowNumber 가져오기
uint8 AWeaponBase::GetRowNumber()
{
	UDataTable* WeaponTable = GetWeaponTable();
	
	RowNames = DT_Weapon->GetRowNames();
	WeaponIdx = FMath::RandRange(1, RowNames.Num());

	return WeaponIdx;
}

// WeaponName 가져오기
FName AWeaponBase::GetWeaponName()
{
	TableIdx = GetRowNumber();
	WeaponNumber = 0000 + TableIdx;

	WeaponName = FString::Printf(TEXT("Weapon%d"), WeaponNumber);

	return *WeaponName;
}

// WeaponPreset(이것도 GameInstance에 옮길수도 있음)
FWeaponPreset AWeaponBase::GetWapPreset()
{
	WeaponData = GetWeaponTable()->FindRow<FWeaponPreset>(GetWeaponName(), TEXT(""));

	return *WeaponData;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}
