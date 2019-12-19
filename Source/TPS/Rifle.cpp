// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"

ARifle::ARifle()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponKind = EWeaponKind::Rifle;
	ConsumeCount = 1.0f;
}

void ARifle::BeginPlay()
{ 
	Super::BeginPlay();

	AmmoInven->GetMaxAmmo(0);

	UE_LOG(LogTemp, Log, TEXT("Rifle Begin"));
}

void ARifle::FireAndAttack_Implementation()
{
	Super::FireAndAttack_Implementation();
}

void ARifle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
