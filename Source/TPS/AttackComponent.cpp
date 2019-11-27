// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"


const int32 UAttackComponent::MaxWeaponSlot = 3;

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UAttackComponent::EquipWeapon(int32 SlotIdx, AWeaponBase* WeaponActor)
{
	// 장착된 무기들 중 해당 인덱스가 없으면 return
	if (EquipedWeapons.IsValidIndex(SlotIdx) == false)
		return;

	if (IsValid(WeaponActor) == false)
		return;

	UBoxComponent* WeaponBoxComponent = Cast<UBoxComponent>(WeaponActor->GetRootComponent());
	WeaponBoxComponent->SetSimulatePhysics(false);
	
	WeaponActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	EquipedWeapons[SlotIdx] = WeaponActor;

	OnChangeCurrentWeapon.Broadcast(WeaponActor, SlotIdx);
}

void UAttackComponent::DropWeapon(int32 SlotIdx)
{
	if (EquipedWeapons.IsValidIndex(SlotIdx) == false)
		return;

	AWeaponBase* Weapon = EquipedWeapons[SlotIdx];
	if (IsValid(Weapon))
		return;
	
	Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	UBoxComponent* WeaponBoxComponent = Cast<UBoxComponent>(Weapon->GetRootComponent());
	WeaponBoxComponent->SetSimulatePhysics(true);
	WeaponBoxComponent->AddImpulse(FVector::UpVector * 1000.0f);
	
	EquipedWeapons[SlotIdx] = nullptr;
	
	CurrentWeaponSlot = -1;

	for (int32 i = 0; i < EquipedWeapons.Num(); i++)
	{
		if (IsValid(EquipedWeapons[i]))
		{
			CurrentWeaponSlot = i;
			return;
		}
	}
}

void UAttackComponent::SetCurrentWeaponSlot(int32 SlotIdx)
{
	if (EquipedWeapons.IsValidIndex(SlotIdx) == false)
		return;
	
	CurrentWeaponSlot = SlotIdx;
}

AWeaponBase* UAttackComponent::GetWeapon(int32 SlotIdx) const
{
	if (EquipedWeapons.IsValidIndex(SlotIdx))
		return EquipedWeapons[SlotIdx];
	else
		return nullptr;
}

float UAttackComponent::GetAttackSpeed() const
{
	if (EquipedWeapons.IsValidIndex(CurrentWeaponSlot) == false)
		return 0.0f;

	if (IsValid(EquipedWeapons[CurrentWeaponSlot]) == false)
		return 0.0f;

	return EquipedWeapons[CurrentWeaponSlot]->WeaponPreset.AttackSpeed;
}

AWeaponBase* UAttackComponent::GetCurrentWeapon() const
{
	int32 Slot = GetCurrentWeaponSlot();

	return GetWeapon(Slot);
}

void UAttackComponent::StartReload()
{
	AWeaponBase* Weapon = GetCurrentWeapon();
	AAmmoInventory* AmmoInven = Cast<AAmmoInventory>(AAmmoInventory::StaticClass());

	if (IsValid(Weapon) == false)
		return;

	if (Weapon->Magazine >= Weapon->WeaponPreset.MagazineCount)
		return;

	if (AmmoInven->GetAmmo(Weapon->WeaponPreset.WeaponKind) <= 0)
		return;

	bReloading = true;
	OnStartReload.Broadcast();
	UE_LOG(LogTemp, Log, TEXT("Start Reload"));
}

void UAttackComponent::CompleteReload()
{
	bReloading = false;
	
	AWeaponBase* Weapon = GetCurrentWeapon();
	AAmmoInventory* AmmoInven = Cast<AAmmoInventory>(AAmmoInventory::StaticClass());

	if (IsValid(Weapon) == false)
		return;

	Weapon->Magazine = AmmoInven->ConsumeAmmo(Weapon->WeaponPreset.WeaponKind, Weapon->WeaponPreset.MagazineCount);

	OnCompleteReload.Broadcast();

	UE_LOG(LogTemp, Log, TEXT("Completed Reload"));
}

void UAttackComponent::Attacking()
{
	if (bCanAttack)
	{
		AWeaponBase* Weapon = GetCurrentWeapon();
		if (IsValid(Weapon))
		{
			GetWorld()->GetTimerManager().SetTimer(WaitAttackTimer
				, this, &UAttackComponent::OnWaitAttackTimerEnd
				, 1.0f / GetAttackSpeed(), false);

			StopAttack();
			Weapon->FireAndAttack();
		}
	}
}

void UAttackComponent::Attack()
{
	bCanAttack = true;
	UE_LOG(LogTemp, Log, TEXT("Attack"));
}

void UAttackComponent::StopAttack()
{
	bCanAttack = false;
	UE_LOG(LogTemp, Log, TEXT("Stop Attack"));
}

void UAttackComponent::OnWaitAttackTimerEnd()
{
	Attack();
}

// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	EquipedWeapons.SetNum(MaxWeaponSlot);
}

// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

