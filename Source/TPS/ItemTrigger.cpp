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
			uint8 SlotIdx = uint8(TPSGameMode->Weapons[CurrentOverlapIndex]->WeaponKind);
			
			/** TODO :: DropWeapon의 호출조건 :: <WeaponKind가 같으면서 Preset의 WeaponId가 다를 경우> 
			 *	-> 장착되어 있는 EquipWeapons[SlotIndex]를 DropWeapon.
			 *	-> CurrentOvelapIndex를 EquipWeapons[SlotIndex]로 등록
			 */ 

			PlayerCharacter->EquipWeapon(SlotIdx, TPSGameMode->Weapons[CurrentOverlapIndex]);

			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
			SetActorTickEnabled(false);

			UE_LOG(LogTemp, Log, TEXT("Overlaped Weapon Index : %d"), CurrentOverlapIndex);
			
			GetWorld()->GetTimerManager().SetTimer(TPSGameMode->WeaponSpawnTimeHandle, TPSGameMode, &ATPSGameModeBase::VisibleTimer, 5.f, false);
		}
	}	
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



