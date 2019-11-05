// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemTrigger.h"

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

	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon Actor"));
	ChildActorComponent->SetupAttachment(BoxCollision);
}

//	if (ChildActorComponent->bVisible)
//	{
//		uint8 WeaponIndex = TPSGameMode->WeaponIdx;
//		TWeaponClass = TPSGameMode->TWeaponArr[WeaponIndex];
//
//		if (TWeaponClass != nullptr)
//		{
//			UE_LOG(LogTemp, Log, TEXT("WeaponIndex : %d"), WeaponIndex);
//		}
//
//		PlayerCharacter->AttachToWeapon(TWeaponClass, WeaponIndex);
//
//		ChildActorComponent->SetVisibility(false, false);
//
//		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AItemTrigger::VisibleTimer, 5.f, false);
//	}
//}

void AItemTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerCharacter == nullptr)
		return;

	if (OtherActor == PlayerCharacter)
	{
		if (!(ExistChildActorComp(ChildActorComponent)))		// ChildActor가 존재하는지 체크
			return;

		if (ChildActorComponent->bVisible)
		{
			ChildActorComponent->SetVisibility(false, false);
			GetWorld()->GetTimerManager().SetTimer(SpawnTimeHandle, this, &AItemTrigger::VisibleTimer, 5.f, false);
		}

	}	
}

void AItemTrigger::VisibleTimer()
{
	ChildActorComponent->SetVisibility(true, false);
}

bool AItemTrigger::ExistChildActorComp(UChildActorComponent* ChildActor)
{
	if (ChildActor == nullptr)
		UE_LOG(LogTemp, Log, TEXT("ChildActor가 존재하지 않습니다."));
		return false;
	
	return true;
}

// Called when the game starts or when spawned
void AItemTrigger::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());

	if (ChildActorComponent != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("ChildActor 존재"));
	}

	FWeaponPreset* Preset = nullptr;
	if (TPSGameInstance->FindWeaponPreset(TPSGameInstance->GetRandomWeaponId(), Preset))
	{
		UE_LOG(LogTemp, Log, TEXT("IsValid(Preset->WeaponAsset : %s"), (IsValid(Preset->WeaponAsset) ? TEXT("VALID") : TEXT("NOT VALID")));
		//if (Preset->WeaponAsset == nullptr)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("WeaponAsset 찾기 실패!!!!"));
		//	return;
		//}
		//ChildActorComponent->SetChildActorClass(Preset->WeaponAsset);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponPreset 찾기 실패!!!!"));
		return;
	}
}

// Called every frame
void AItemTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//RotationAngle += DeltaSeconds * 0.06f;

	//FRotator WeaponRotation = FRotator::ZeroRotator;
	//WeaponRotation.Yaw = RotationAngle;

	//if (ChildActorComponent == nullptr)
	//	return;

	//ChildActorComponent->AddRelativeRotation(WeaponRotation);

}



