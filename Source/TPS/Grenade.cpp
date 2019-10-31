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
}

void AGrenade::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
