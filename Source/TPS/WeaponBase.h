// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "AttackComponent.h"

#include "WeaponBase.generated.h"

class UTPSGameInstance;
class AAmmoInventory;
class ATPSCharacter;

UENUM(BlueprintType)
enum class EWeaponKind : uint8
{
	Rifle,
	Knife,
	Grenade,
	Default
};

USTRUCT(BlueprintType)
struct TPS_API FWeaponPreset : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponKind WeaponKind;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FText DisplayName = FText::GetEmpty();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AWeaponBase> WeaponAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireDelay = 0.0f;
};

UCLASS(Abstract)
class TPS_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* WeaponTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AAmmoInventory* AmmoInven;

public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Kind")
	EWeaponKind WeaponKind;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void FireAndAttack();
	virtual void FireAndAttack_Implementation();

public:

	UFUNCTION(BlueprintCallable)
	float GetAmmo() const { return Ammo; }

	UFUNCTION(BlueprintCallable)
	float GetConsumeCount() const { return ConsumeCount; }

	UFUNCTION(BlueprintCallable)
	bool IsAmmoEmpty() const { return Ammo <= 0; }

	UFUNCTION(BlueprintCallable)
	UTPSGameInstance* GetTPSGameInstance() const { return TPSGameInstance; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter = GetAmmo, Category = "Ammo Info")
	float Ammo = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter = GetConsumeCount, Category = "Ammo Info")
	float ConsumeCount = 0.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FWeaponPreset* WeaponPreset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTPSGameInstance* TPSGameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ATPSCharacter* TPSPlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAttackComponent* AttackComponent;

private:

	UPROPERTY(VisibleAnywhere)
	FString WeaponName;

	//UPROPERTY(VisibleAnywhere)
	//float RotationAngle = 0.0f;
};
