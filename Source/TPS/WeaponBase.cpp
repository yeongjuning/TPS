﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "TPSGameInstance.h"
#include "AmmoInventory.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
}

// Called every frame
void AWeaponBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}
