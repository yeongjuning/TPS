// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "TPSCharacter.h"
#include "TPSGameState.h"
#include "AIController.h"
#include "Engine/DataTable.h"

#include "EnemyCharacter.generated.h"

USTRUCT(BlueprintType)
struct TPS_API FEnemyPreset: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<ATPSCharacter> CharacterAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USkeletalMesh> SkeletalMeshAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<AAIController> AIControllerClass = nullptr;

	// 스테이지당 나올 몬스터 담는 배열
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> RowNameList;
};

UCLASS()
class TPS_API AEnemyCharacter : public ATPSCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION(BlueprintCallable)
	virtual void Dead_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual void Attack_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual void StopAttack_Implementation() override;

	virtual void BeginPlay() override;
};
