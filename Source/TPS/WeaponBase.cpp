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

	//BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	//RootComponent = BoxComponent;
	//BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//BoxComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
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
}

// Called every frame
void AWeaponBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
