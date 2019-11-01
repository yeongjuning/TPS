// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "TPSGameInstance.h"
#include "AmmoInventory.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// RowNumber 가져온다
uint8 AWeaponBase::GetRowNumber()
{
	WeaponTable = TPSGameInstance->GetWeaponTable();
	
	RowNames = WeaponTable->GetRowNames();
	WeaponIdx = FMath::RandRange(1, RowNames.Num());	

	return WeaponIdx;
}

// 이부분을 EWeaponKind형태로 바꿔준후 돌려주기
FName AWeaponBase::GetWeaponName()
{
	TableIdx = GetRowNumber();

	WeaponName = FString::Printf(TEXT("Weapon%d"), TableIdx);
	UE_LOG(LogTemp, Log, TEXT("%s"), &WeaponName);
	return *WeaponName;
}

// WeaponPreset
void AWeaponBase::SetWeaponPreset()
{
	WeaponPreset = TPSGameInstance->GetWeaponTable()->FindRow<FWeaponPreset>(GetWeaponName(), TEXT(""));

	if (WeaponPreset == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("무기 프리셋 데이터를 찾지 못했습니다."));
		return;
	}
}

// UClass 형으로  Asset을 찾아 Class형태로 Return
UClass* AWeaponBase::GetWeaponClass()
{
	WeaponClass = WeaponPreset->WeaponAsset.LoadSynchronous();
	
	if (WeaponClass == nullptr)
		UE_LOG(LogTemp, Error, TEXT("무기 에셋을 찾지 못했습니다."));
		return nullptr;

	return WeaponClass;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
}

// Called every frame
void AWeaponBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}
