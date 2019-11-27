// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerAnimInstance.h"
#include "TPSCharacter.h"
#include "AttackComponent.h"
#include "WeaponBase.h"

//void UTPSPlayerAnimInstance::ChangeCurrentWeapon(AWeaponBase* ChangedWeapon, int32 SlotIndex)
//{
//	if (IsValid(ChangedWeapon) == false)
//		return;
//
//	AttackSpeed = ChangedWeapon->WeaponPreset.AttackSpeed;
//}
//
//void UTPSPlayerAnimInstance::NativeBeginPlay()
//{
//	Super::NativeBeginPlay();
//
//	ATPSCharacter* TPSCharacter = Cast<ATPSCharacter>(TryGetPawnOwner());
//	if (IsValid(TPSCharacter) == false)
//		return;
//	
//	TPSCharacter->GetAttackComponent()->OnChangeCurrentWeapon.AddDynamic(this, &UTPSPlayerAnimInstance::ChangeCurrentWeapon);
//}
//
//void UTPSPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
//{
//	Super::NativeUpdateAnimation(DeltaSeconds);
//
//	ATPSCharacter* TPSCharacter = Cast<ATPSCharacter>(TryGetPawnOwner());
//	if (IsValid(TPSCharacter) == false)
//		return;
//
//	UAttackComponent* AttackComponent = TPSCharacter->GetAttackComponent();
//	if (IsValid(AttackComponent) == false)
//		return;
//
//	FVector Velocity = TPSCharacter->GetVelocity();
//
//	Speed = Velocity.Size();
//	Direction = CalculateDirection(Velocity, TPSCharacter->GetActorRotation());
//	bAttacking = AttackComponent->IsAttacking();
//	bReloading = AttackComponent->IsReloading();
//}
