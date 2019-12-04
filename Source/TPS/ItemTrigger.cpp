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
		for (int32 i = 0; i < TPSGameMode->SpawnCount; i++)
		{
			if (TPSGameMode->Weapons.IsValidIndex(i))
			{
				uint8 SlotIdx = uint8(TPSGameMode->Weapons[i]->WeaponKind);
				PlayerCharacter->EquipWeapon(SlotIdx, TPSGameMode->Weapons[i]);

				SetActorHiddenInGame(true);
				SetActorEnableCollision(false);
				SetActorTickEnabled(false);

				UE_LOG(LogTemp, Log, TEXT("Weapons[%d] EquipWeapon"), i);
			}
		}
		//if (IsValid(Weapon))
		//{
		//	uint8 SlotIdx = uint8(Weapon->WeaponKind);
		//	
		//	PlayerCharacter->EquipWeapon(SlotIdx, Weapon);

		//	SetActorHiddenInGame(true);
		//	SetActorEnableCollision(false);
		//	SetActorTickEnabled(false);

		//	GetWorld()->GetTimerManager().SetTimer(SpawnTimeHandle, this, &AItemTrigger::VisibleTimer, 5.f, false);
		//}
	}	
}

void AItemTrigger::VisibleTimer()
{	
	// 임시방편
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);

	//// Respawn시 Random 위치 Weapon의 RandomId
	//WeaponSpawn(TPSGameInstance->GetRandomWeaponId(), WeaponPreset);
}

// Called when the game starts or when spawned
void AItemTrigger::BeginPlay()
{
	Super::BeginPlay();

	TPSGameMode = GetWorld()->GetAuthGameMode<ATPSGameModeBase>();

	PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());	// 일단 냅두기

	//CurSpawnedWeaponId = TPSGameInstance->GetRandomWeaponId();
	//WeaponSpawn(CurSpawnedWeaponId, WeaponPreset);
}

void AItemTrigger::WeaponSpawn(FName SpawnedId, FWeaponPreset Preset)
{
	if (TPSGameInstance->FindWeaponPreset(SpawnedId, Preset))
	{
		FActorSpawnParameters Parameters;
		Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		Weapon = GetWorld()->SpawnActor<AWeaponBase>
			(Preset.WeaponActor, TPSGameMode->GetWeaponTransform(), Parameters);
	}
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



