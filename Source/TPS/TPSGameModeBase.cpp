// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameModeBase.h"

ATPSGameModeBase::ATPSGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

// SpawnPoint
int32 ATPSGameModeBase::GetWeaponSpawnPoint()
{
	int32 WapSpawnPoint = FMath::RandRange(0, WapSpawnPoints.Num() - 1);
	UE_LOG(LogTemp, Log, TEXT("SpawnPoint Of Weapon: %d"), WapSpawnPoint);

	return WapSpawnPoint;
}

// Spawned Weapon Trnasform
FTransform ATPSGameModeBase::GetWeaponTransform()
{
	SpawnPoint = GetWeaponSpawnPoint();

	SpawnTransform = WapSpawnPoints[SpawnPoint]->GetActorTransform();
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	return SpawnTransform;
}

// Trigger Spawn
void ATPSGameModeBase::SpawnTrigger()
{
	FTransform SpawnTF = GetWeaponTransform();

	UClass* TriggerClass= AItemTrigger::StaticClass();
	GetWorld()->SpawnActor<AItemTrigger>(TriggerClass, SpawnTF, Parameters);
}

void ATPSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWeaponSpawner::StaticClass(), WapSpawnPoints);

	SpawnTrigger();
	
}
