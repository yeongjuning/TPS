// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"

AGrenade::AGrenade()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponKind = EWeaponKind::Grenade;

	ConsumeCount = 1.0f;
}

void AGrenade::BeginPlay()
{
	Super::BeginPlay();

	Ammo = AmmoInven->GetMaxAmmo();
	UE_LOG(LogTemp, Log, TEXT("%d"), Ammo);
}

void AGrenade::FireAndAttack_Implementation()
{
	Super::FireAndAttack_Implementation();
}

void AGrenade::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
