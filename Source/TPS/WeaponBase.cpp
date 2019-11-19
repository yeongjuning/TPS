// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "TPSGameInstance.h"
#include "AmmoInventory.h"
#include "TPSCharacter.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponBase::FireAndAttack_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Fire And Attack"));
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
	TPSPlayerCharacter = Cast<ATPSCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	
	AttackComponent = TPSPlayerCharacter->GetAttackComponent();
}

// Called every frame
void AWeaponBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//if (this == nullptr)
	//	return;

	//RotationAngle += DeltaSeconds * 0.06f;

	//FRotator WeaponRotation = FRotator::ZeroRotator;
	//WeaponRotation.Yaw = RotationAngle;

	//this->SetActorRelativeRotation(WeaponRotation);
}
