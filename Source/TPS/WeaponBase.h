// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AWeaponBase> WeaponActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagazineCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireDelay = 0.0f;
};

UCLASS()
class TPS_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	FWeaponPreset WeaponPreset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Magazine = 0;

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

	UFUNCTION(BlueprintCallable)
	UBoxComponent* GetBoxComponent() const { return BoxComponent; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter = GetAmmo, Category = "Ammo Info")
	float Ammo = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter = GetConsumeCount, Category = "Ammo Info")
	float ConsumeCount = 0.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter = GetTPSGameInstance)
	UTPSGameInstance* TPSGameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ATPSCharacter* TPSPlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter = GetBoxComponent)
	UBoxComponent* BoxComponent;
};
