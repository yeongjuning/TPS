// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameModeBase.h"

ATPSGameModeBase::ATPSGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

int32 ATPSGameModeBase::GetWeaponSpawnPoint()
{
	int32 WapSpawnPoint = FMath::RandRange(0, WapSpawnPoints.Num() - 1);
	UE_LOG(LogTemp, Log, TEXT("SpawnPoint Of Weapon: %d"), WapSpawnPoint);

	return WapSpawnPoint;
}

FTransform ATPSGameModeBase::GetWeaponTransform()
{
	int32 SpawnPoint = GetWeaponSpawnPoint();

	SpawnTransform = WapSpawnPoints[SpawnPoint]->GetActorTransform();
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	return SpawnTransform;
}

AItemTrigger* ATPSGameModeBase::SpawnTrigger()
{
	FTransform SpawnTF = GetWeaponTransform();

	UClass* TriggerClass= AItemTrigger::StaticClass();
	ItemTrigger = GetWorld()->SpawnActor<AItemTrigger>(TriggerClass, SpawnTF, Parameters);

	return ItemTrigger;
}

void ATPSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
}
