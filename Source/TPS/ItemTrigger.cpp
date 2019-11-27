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
	AttackComponent->SetupAttachment(BoxCollision, TEXT("Weapon Actor"));
}

void AItemTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlap Trigger"));

	if (PlayerCharacter == nullptr)
		return;

	if (OtherActor == PlayerCharacter)
	{
		//if (ChildActorComponent->bVisible)
		//{
		//	// 현재 Spawn된 WeaponId를 받아서 장착부근에 어떤 무기인지 넘겨주기
		//	PlayerCharacter->EquipWeapon(WeaponPreset.WeaponAsset, WeaponPreset.WeaponKind);
		//	ChildActorComponent->SetVisibility(false, false);
		//	GetWorld()->GetTimerManager().SetTimer(SpawnTimeHandle, this, &AItemTrigger::VisibleTimer, 5.f, false);
		//}

	}	
}

//void AItemTrigger::VisibleTimer()
//{
//	ChildActorComponent->SetVisibility(true, false);
//}

// Called when the game starts or when spawned
void AItemTrigger::BeginPlay()
{
	Super::BeginPlay();

	TPSGameMode = GetWorld()->GetAuthGameMode<ATPSGameModeBase>();

	PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());	// 일단 냅두기
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



