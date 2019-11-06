// Fill out your copyright notice in the Description page of Project Settings.


#include "Knife.h"

AKnife::AKnife()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponKind = EWeaponKind::Knife;
	ConsumeCount = 0;
}

void AKnife::BeginPlay()
{
	Super::BeginPlay();

	Ammo = AmmoInven->GetMaxAmmo();
	UE_LOG(LogTemp, Log, TEXT("%d"), Ammo);
}

void AKnife::FireAndAttack_Implementation()
{
	Super::FireAndAttack_Implementation();
}

void AKnife::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}