// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Components/SceneComponent.h"
#include "TPSGameModeBase.h"
#include "WeaponBase.h"
#include "AmmoInventory.h"

#include "AttackComponent.generated.h"

class ATPSCharacter;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReloadSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_API UAttackComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	static const int32 MaxWeaponSlot;

	UPROPERTY(BlueprintAssignable)
	FReloadSignature OnStartReload;

	UPROPERTY(BlueprintAssignable)
	FReloadSignature OnCompleteReload;

	//// 무기가 변경될 때 마다 변경될 애니매이션
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	//TMap<EWeaponKind, TSubclassOf<UAnimInstance>> WeaponAnimClasses;
	
public:

	// 현재 들고 있는 무기를 재장전
	UFUNCTION(BlueprintCallable)
	void StartReload();

	// 재장전이 완료되면 호출
	UFUNCTION(BlueprintCallable)
	void CompleteReload();

	UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintCallable)
	void StopAttack();

public:	
	// Sets default values for this component's properties
	UAttackComponent();

	UFUNCTION(BlueprintCallable)
	bool IsAttacking() const { return bCanAttack; }

	UFUNCTION(BlueprintCallable)
	bool IsReloading() const { return bReloading; }

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	FTimerHandle WaitAttackTimer;

	void OnWaitAttackTimerEnd();

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	ATPSCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere)
	ATPSGameModeBase* TPSGameMode;

private:

	UPROPERTY(VisibleAnywhere, BlueprintGetter = IsAttacking)
	bool bCanAttack = false;

	UPROPERTY(VisibleAnywhere, BlueprintGetter = IsReloading)
	bool bReloading = false;
};
