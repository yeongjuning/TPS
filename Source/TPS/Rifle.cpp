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

	// TODO Rifle에서 TEST 이후 knife나 Grenade 넣어주기
	Ammo = AmmoInven->GetMaxAmmo();
	UE_LOG(LogTemp, Log, TEXT("%d"), Ammo);
}

void ARifle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
