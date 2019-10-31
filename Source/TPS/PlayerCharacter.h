// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "TPSCharacter.h"

#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API APlayerCharacter : public ATPSCharacter
{
	GENERATED_BODY()

public:

	APlayerCharacter();
	
	UFUNCTION()
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	UFUNCTION()
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	
	UFUNCTION()
	FORCEINLINE UChildActorComponent* GetChildWeapon() const { return ChildWeapon; }

protected:
	UFUNCTION(BlueprintCallable)
	virtual void Attack_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual void StopAttack_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual void Reload_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual void StopReload_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual void Dead_Implementation() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ChildWeapon;

protected:

	//UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, BlueprintGetter = GetTPSPlayerStatus, Category = "Status of Player")
	//APlayerStatus* PlayerStatus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D MovementInput;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D CameraInput;

	UFUNCTION(BlueprintCallable)
	void ZoomToDeath();

	UFUNCTION(BlueprintCallable)
	void PitchCamera(float AxisValue);

	UFUNCTION(BlueprintCallable)
	void YawCamera(float AxisValue);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
