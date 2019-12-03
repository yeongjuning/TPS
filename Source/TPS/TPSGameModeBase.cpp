// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameModeBase.h"
#include "ItemTrigger.h"

ATPSGameModeBase::ATPSGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

/**********************************WeaponSpawn****************************************/

// SpawnPoint
int32 ATPSGameModeBase::GetRandomWeaponSpawnPoint() const
{
	return FMath::RandRange(0, WapSpawnPoints.Num() - 1);
}

// TODO TEST
int32 ATPSGameModeBase::GetRandomWeaponSpawnCount()
{
	return int32();
}

// RandomCount

// Spawned Weapon Trnasform
FTransform ATPSGameModeBase::GetRandomWeaponTransform()
{
	WapSpawnPoint = GetRandomWeaponSpawnPoint();

	RandomWapSpawnTransform = WapSpawnPoints[WapSpawnPoint]->GetActorTransform();
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	return RandomWapSpawnTransform;
}

// Trigger Spawn
void ATPSGameModeBase::SpawnTrigger()
{
	WeaponTransform = GetRandomWeaponTransform();

	UClass* TriggerClass= AItemTrigger::StaticClass();
	SpawnedTrigger = GetWorld()->SpawnActor<AItemTrigger>(TriggerClass, WeaponTransform, Parameters);
}

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
	/** todo:: EnemyDataTable�� �ִ� Row������� Spawn
	 * 1. ������ �����ϸ� �� �� �� Count��ŭ ù��° Row�� Spawn
	 * 2. ������ Enemy�� Count�� ��� ���̸� ���� Row�� �Ѿư��� Spawn
	 * 3. ��� Row�� ����Ǹ� Spawn�� ������ Clear;
	 */ 

}

void ATPSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWeaponSpawner::StaticClass(), WapSpawnPoints);
	
	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
	
	SpawnTrigger();
}
