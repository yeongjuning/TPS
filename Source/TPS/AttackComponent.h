// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPS_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool Attack() const { return bAttack; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool StopAttack() const { return !bAttack; }

	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintGetter = Attack, Category = "Possible Behavior")
	bool bAttack = false;

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
