// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "TPSGameInstance.h"
#include "WeaponBase.h"

#include "ItemTrigger.generated.h"

class ATPSGameModeBase;

UCLASS()
class TPS_API AItemTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemTrigger();

	FORCEINLINE AWeaponBase* GetWeapon() const { return Weapon; }
	/*FORCEINLINE TSubclassOf<AWeaponBase*> GetWeaponClass() const { return TWeaponClass; }*/
	FORCEINLINE UBoxComponent* GetBoxCollision() const { return BoxCollision; }
	FORCEINLINE UChildActorComponent* GetChildActorComponent() const { return ChildActorComponent; }

public:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
		void OnOverlapBegin
		(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
	void VisibleTimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ATPSGameModeBase* TPSGameMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTPSGameInstance* TPSGameInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UChildActorComponent* ChildActorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerCharacter* PlayerCharacter;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//TArray<TSubclassOf<AWeaponBase*>> TWeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AWeaponBase* Weapon;

	FTimerHandle SpawnTimeHandle;

private:

	UPROPERTY(VisibleAnywhere)
	float RotationAngle = 0.0f;

	UPROPERTY(VisibleAnywhere)
	FName CurSpawnedWeaponId;
};
