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
AItemTrigger* ATPSGameModeBase::SpawnTrigger()
{
	FTransform SpawnTF = GetWeaponTransform();

	UClass* TriggerClass= AItemTrigger::StaticClass();
	ItemTrigger = GetWorld()->SpawnActor<AItemTrigger>(TriggerClass, SpawnTF, Parameters);

	return ItemTrigger;
}

// Finised WeaponSpawn
void ATPSGameModeBase::WeaponSpawn()
{
	AItemTrigger* Trigger = SpawnTrigger();

	UChildActorComponent* ChildActorComponent = Trigger->GetChildActorComponent();
	if (Weapon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Should't Weapon Casting"));
		return;
	}
	// AWeaponBase의 cpp에서 Preset 가져오기
	Weapon->GetWeaponClass();
	if (WeaponClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponAsset isn't Loaded"));
		return;
	}

	ChildActorComponent->SetChildActorClass(WeaponClass);
}

void ATPSGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWeaponSpawner::StaticClass(), WapSpawnPoints);
	
	WeaponSpawn();
}
