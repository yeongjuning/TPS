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

			uint8 SlotIdx = uint8(TPSGameMode->Weapons[CurrentOverlapIndex]->WeaponKind);

			if (bIsTheSameWeapon(CurrentOverlapIndex, SlotIdx) == false)
			{
				PlayerCharacter->EquipWeapon(SlotIdx, TPSGameMode->Weapons[CurrentOverlapIndex]);
				PlayerCharacter->SetEquipedWeaponId(CurrentOverlapIndex, SlotIdx);
				SetSpawnedActorHidden();
				
				TPSGameMode->Weapons[CurrentOverlapIndex] = nullptr;
				TPSGameMode->Triggers[CurrentOverlapIndex] = nullptr;

				CurrentOverlapIndex = -1;
				
				for (int32 i = 0; i < TPSGameMode->Weapons.Num(); i++)
				{
					if (IsValid(TPSGameMode->Weapons[i]))
					{
						CurrentOverlapIndex = i;
						UE_LOG(LogTemp, Log, TEXT("남은 스폰 인덱스 : %d"), CurrentOverlapIndex);

						return;
					}
				}

				// For문을 돌려서 VisibleTimer를 호출시킨다?
				GetWorld()->GetTimerManager().SetTimer(TPSGameMode->WeaponSpawnTimeHandle, TPSGameMode, &ATPSGameModeBase::VisibleTimer, 5.f, false);
			}
		}
	}	
}

bool AItemTrigger::bIsTheSameWeapon(int32 Current, uint8 Slot) const
{
	AWeaponBase* Spawned = TPSGameMode->Weapons[Current];

	if (IsValid(PlayerCharacter->GetWeapon(Slot)) == false)
	{
		UE_LOG(LogTemp, Log, TEXT("현재 장착된 무기가 존재하지 않아 그대로 장착가능합니다."));
		return false;
	}

	if (Spawned == PlayerCharacter->GetEquipedWeapons()[Slot])
	{
		UE_LOG(LogTemp, Log, TEXT("스폰된 무기 ID와 현재 장착된 무기 ID가 같습니다."));
		return true;
	}

	return false;
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



