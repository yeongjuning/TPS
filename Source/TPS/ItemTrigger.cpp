// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemTrigger.h"
#include "TPSGameModeBase.h"

// Sets default values
AItemTrigger::AItemTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Trigger"));
	RootComponent = BoxCollision;
	BoxCollision->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
	BoxCollision->SetupAttachment(RootComponent);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemTrigger::OnOverlapBegin);

	AttackComponent = CreateDefaultSubobject<UAttackComponent>(FName(TEXT("Attack Component")));
	AttackComponent->SetupAttachment(BoxCollision);
}

void AItemTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerCharacter == nullptr)
		return;

	if (OtherActor == PlayerCharacter)
	{
		if (TPSGameMode->Weapons.IsValidIndex(CurrentOverlapIndex))
		{
			UE_LOG(LogTemp, Log, TEXT("Overlaped Weapon Index : %d"), CurrentOverlapIndex);

			AWeaponBase* Weapon = TPSGameMode->Weapons[CurrentOverlapIndex];
			uint8 SlotIdx = uint8(Weapon->WeaponKind);

			if (bIsSameWeaponEquipped(SlotIdx) == false)
			{
				PlayerCharacter->EquipWeapon(SlotIdx, Weapon);
				PlayerCharacter->SetEquipedWeaponId(CurrentOverlapIndex, SlotIdx);
				SetSpawnedActorHidden();
				
				TPSGameMode->IndexReduction(CurrentOverlapIndex);
				GetWorld()->GetTimerManager().SetTimer(TPSGameMode->WeaponSpawnTimeHandle, TPSGameMode, &ATPSGameModeBase::VisibleTimer, 5.f, false);
			}
			else
			{
				AmmoInventory->AddAmmo(Weapon->WeaponKind, AmmoInventory->GetMaxAmmo(SlotIdx));
			}
		}
	}	
}

bool AItemTrigger::bIsSameWeaponEquipped(uint8 Slot) const
{
	if (IsValid(PlayerCharacter->GetWeapon(Slot)) == false)
		return false;
	else
		return true;
}

void AItemTrigger::SetSpawnedActorHidden()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}

// Called when the game starts or when spawned
void AItemTrigger::BeginPlay()
{
	Super::BeginPlay();

	TPSGameMode = GetWorld()->GetAuthGameMode<ATPSGameModeBase>();

	PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());	// 일단 냅두기
	
	AmmoInventory = TPSGameInstance->GetAmmoInventory();

	CurrentOverlapIndex = TPSGameMode->SpawnIndex;
}

// Called every frame
void AItemTrigger::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//RotationAngle += DeltaSeconds * 0.06f;

	//FRotator WeaponRotation = FRotator::ZeroRotator;
	//WeaponRotation.Yaw = RotationAngle;

	//if (ChildActorComponent == nullptr)
	//	return;

	//ChildActorComponent->AddRelativeRotation(WeaponRotation);
}



