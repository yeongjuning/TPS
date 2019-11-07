// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameModeBase.h"

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
	UClass* TriggerClass= AItemTrigger::StaticClass();
	GetWorld()->SpawnActor<AItemTrigger>(TriggerClass, GetRandomWeaponTransform(), Parameters);
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

	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWeaponSpawner::StaticClass(), WapSpawnPoints);

	SpawnTrigger();
	
}
