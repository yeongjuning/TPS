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
	/** todo:: EnemyDataTable에 있는 Row순서대로 Spawn
	 * 1. 게임이 시작하면 몇 초 뒤 Count만큼 첫번째 Row가 Spawn
	 * 2. 나오는 Enemy의 Count를 모두 죽이면 다음 Row로 넘아가서 Spawn
	 * 3. 모든 Row가 종료되면 Spawn을 끝내고 Clear;
	 */ 

}

void ATPSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWeaponSpawner::StaticClass(), WapSpawnPoints);

	SpawnTrigger();
	
}
