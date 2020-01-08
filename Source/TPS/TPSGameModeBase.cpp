// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameModeBase.h"
#include "ItemTrigger.h"

ATPSGameModeBase::ATPSGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

/**********************************WeaponSpawn****************************************/

// TODO TEST :: 월드에 배치된 SpawnPoint들 중에서 랜덤한 갯수로 해당 Point에 Spawn	//
int32 ATPSGameModeBase::GetRandomWeaponSpawnCount()
{
	return FMath::RandRange(1, WapSpawnPoints.Num());
}

FTransform ATPSGameModeBase::GetRandomWeaponSpawnPoint()
{
	return WapSpawnPoints[FMath::RandRange(0, WapSpawnPoints.Num() - 1)]->GetActorTransform();
}

void ATPSGameModeBase::RandomTriggerSpawn(int32 InputIndex, FTransform InputTransform)
{
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	TriggerClass = AItemTrigger::StaticClass();
	Triggers[InputIndex] = GetWorld()->SpawnActor<AItemTrigger>(TriggerClass, InputTransform, Parameters);
}

void ATPSGameModeBase::RandomWeaponSpawn()
{
	int32 SpawnCount = GetRandomWeaponSpawnCount();
	SetArrRelatedToWeaponSpawn(SpawnCount);

	for (SpawnIndex = 0; SpawnIndex < SpawnCount; SpawnIndex++)
	{
		RandTransform[SpawnIndex] = GetRandomWeaponSpawnPoint();

		if (RandTransform.IsValidIndex(SpawnIndex))
		{	
			if (CheckEqulRandomTransform(SpawnIndex, SpawnCount))
				break;

			RandomTriggerSpawn(SpawnIndex, RandTransform[SpawnIndex]);					// Trigger 스폰
			CurSpawnedWeaponIds[SpawnIndex] = TPSGameInstance->GetRandomWeaponId();		// WeaponId 가져오기
			SetCurrentSpawnedIdIndex(SpawnIndex);										// 현재 Spawn된 WeaponId 셋팅
			WeaponsSpawn(SpawnIndex, CurSpawnedWeaponIds[SpawnIndex], WeaponPreset);	// Id에 맞는 Weapon을 스폰
		}
	}
}

bool ATPSGameModeBase::CheckEqulRandomTransform(int32 TransIdx, int32 Count) const
{
	if (TransIdx > 0 && Count > 1)
	{
		for (int32 i = 0; i < TransIdx; i++)
		{
			if (RandTransform[i].GetLocation() == RandTransform[TransIdx].GetLocation())
				return true;	
		}
	}

	return false;
}

void ATPSGameModeBase::WeaponsSpawn(int32 TriggerIdx, FName SpawnId, FWeaponPreset Preset)
{
	if (TPSGameInstance->FindWeaponPreset(SpawnId, Preset))
	{
		if (Weapons.IsValidIndex(TriggerIdx))
		{
			Weapons[TriggerIdx] = GetWorld()->SpawnActor<AWeaponBase>
				(Preset.WeaponActor, RandTransform[TriggerIdx], Parameters);

			int32 WeaponMaxAmmo = Weapons[TriggerIdx]->AmmoInven->GetMaxAmmo(int32(Preset.WeaponKind));

			Weapons[TriggerIdx]->AmmoInven->AddAmmo(Preset.WeaponKind, WeaponMaxAmmo);
			WeaponAmmo = Weapons[TriggerIdx]->AmmoInven->GetAmmo(Preset.WeaponKind);
		}
	}
}

void ATPSGameModeBase::SetArrRelatedToWeaponSpawn(int32 ArrLength)
{
	SpawnArrLength += ArrLength;
	
	RandTransform.SetNum(SpawnArrLength);
	CurSpawnedWeaponIds.SetNum(SpawnArrLength);
	Weapons.SetNum(SpawnArrLength);
	Triggers.SetNum(SpawnArrLength);
}

//======================================================================//
void ATPSGameModeBase::SetCurrentSpawnedIdIndex(int32 WeaponIdIndex)
{
	if (CurSpawnedWeaponIds.IsValidIndex(WeaponIdIndex) == false)
		return;

	CurrentSpawnedIndex = WeaponIdIndex;
}

FName ATPSGameModeBase::GetSpawnedId(int32 WeaponIdIndex) const
{
	if (CurSpawnedWeaponIds.IsValidIndex(WeaponIdIndex))
		return CurSpawnedWeaponIds[WeaponIdIndex];
	else
		return FName();
}

FName ATPSGameModeBase::GetCurrentSpawnedId() const
{
	int32 Spawned = GetCurrentSpawnedIndex();

	return GetSpawnedId(Spawned);
}

void ATPSGameModeBase::IndexReduction(int32 OverlapIndex)
{
	Weapons[OverlapIndex] = nullptr;
	Triggers[OverlapIndex] = nullptr;

	OverlapIndex = -1;

	for (int32 i = 0; i < Weapons.Num(); i++)
	{
		if (IsValid(Weapons[i]))
		{
			OverlapIndex = i;
			UE_LOG(LogTemp, Log, TEXT("IndexReduction() : %d"), OverlapIndex);
			return;
		}
	}
}

void ATPSGameModeBase::VisibleTimer()
{
	UE_LOG(LogTemp, Log, TEXT("=====================Respawn====================="));
	RandomWeaponSpawn();
}

//================================================================================//
/**********************************EnemySpawn****************************************/

int32 ATPSGameModeBase::GetRandomEnemySpawnPoint() const
{
	return FMath::RandRange(0, EnemySpawnPoints.Num() - 1);
}

FTransform ATPSGameModeBase::GetRandomEnemyTransform()
{
	EnemySpawnPoint = GetRandomEnemySpawnPoint();

	RandomEnemySpawnTransform = EnemySpawnPoints[EnemySpawnPoint]->GetActorTransform();
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	return RandomEnemySpawnTransform;
}

void ATPSGameModeBase::SpawnEnemy()
{
	/** todo:: EnemyDataTable에 있는 Row순서대로 Spawn
	 * 1. 게임이 시작하면 몇 초 뒤 Count만큼 첫번째 Row가 Spawn
	 * 2. 나오는 Enemy의 Count를 모두 죽이면 다음 Row로 넘아가서 Spawn
	 * 3. 모든 Row가 종료되면 Spawn을 끝내고 Clear;
	 */ 

}

void ATPSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWeaponSpawner::StaticClass(), WapSpawnPoints);
	
	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
	
	UE_LOG(LogTemp, Log ,TEXT("TPS Game Mode Base 시작!!"));

	RandomWeaponSpawn();
}