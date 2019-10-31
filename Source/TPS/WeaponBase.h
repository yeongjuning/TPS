// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"

#include "WeaponBase.generated.h"

class UTPSGameInstance;
class AAmmoInventory;

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
	TSoftClassPtr<AWeaponBase> WeaponAsset = nullptr;

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

	UFUNCTION(BlueprintCallable)
	uint8 GetRowNumber();

	UFUNCTION(BlueprintCallable)
	FName GetWeaponName();

	UFUNCTION(BlueprintCallable)
	void SetWeaponPreset();

	UFUNCTION(BlueprintCallable)
	UClass* GetWeaponClass();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	TArray<FName> RowNames;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	uint8 WeaponIdx;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Table Key")
	int32 TableIdx;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Class")
	UClass* WeaponClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Kind")
	EWeaponKind WeaponKind;
	
public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetAmmo() const { return Ammo; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetConsumeCount() const { return ConsumeCount; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsAmmoEmpty() const { return bIsAmmoEmpty; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTPSGameInstance* GetTPSGameInstance() const { return TPSGameInstance; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter = GetAmmo, Category = "Ammo Info")
	float Ammo = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter = GetConsumeCount, Category = "Ammo Info")
	float ConsumeCount = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter = IsAmmoEmpty, Category = "Ammo Info")
	bool bIsAmmoEmpty = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FWeaponPreset* WeaponPreset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTPSGameInstance* TPSGameInstance;

private:

	UPROPERTY(VisibleAnywhere)
	FString WeaponName;
};
