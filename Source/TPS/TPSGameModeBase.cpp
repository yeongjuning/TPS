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

void ATPSGameModeBase::RandomSpawnTrigger()
{
	SpawnCount = GetRandomWeaponSpawnCount();																																																																																																																								
	SetArraiesLength(SpawnCount);

	for (int32 i = 0; i < SpawnCount; i++)
	{
		RandTransform[i] = GetRandomWeaponSpawnPoint();

		if (RandTransform.IsValidIndex(i))
		{	
			if (CheckEqulTransform(i, SpawnCount))
				break;

			UE_LOG(LogTemp, Log, TEXT("%d번째 Transform :: (X:%f), (Y:%f), (Z:%f)"), i,
				RandTransform[i].GetLocation().X,
				RandTransform[i].GetLocation().Y,
				RandTransform[i].GetLocation().Z);

			Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			UClass* TriggerClass = AItemTrigger::StaticClass();
			Triggers[i] = GetWorld()->SpawnActor<AItemTrigger>(TriggerClass, RandTransform[i], Parameters);
			
			CurSpawnedWeaponIds[i] = TPSGameInstance->GetRandomWeaponId();
			WeaponsSpawn(i, CurSpawnedWeaponIds[i], WeaponPreset);
		}
	}
}

// 랜덤으로 책정된 Count수 만큼 Spawn됬을 때, 같은 Transform인지 확인
bool ATPSGameModeBase::CheckEqulTransform(int32 TransIdx, int32 Count) const
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
			UE_LOG(LogTemp, Log, TEXT("WeaponSpawnIdx : %d"), TriggerIdx);
			Weapons[TriggerIdx] = GetWorld()->SpawnActor<AWeaponBase>
				(Preset.WeaponActor, RandTransform[TriggerIdx], Parameters);
		}
	}
}

void ATPSGameModeBase::SetArraiesLength(int32 ArrLength)
{
	RandTransform.SetNum(ArrLength);
	CurSpawnedWeaponIds.SetNum(ArrLength);
	Weapons.SetNum(ArrLength);
	Triggers.SetNum(ArrLength);
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

	RandomSpawnTrigger();

}
