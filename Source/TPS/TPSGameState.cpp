// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameState.h"

ATPSGameState::ATPSGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATPSGameState::ChangeOfState()
{
	//Cast<ATPSGameState>(GetWorld()->GetGameState())->GamePlayingState != EGamePlayingState::Playing

	//ATPSCharacter* TPSCharacter;
	//
	//if (TPSCharacter->GetIsDead() == true)
	//{
	//	GamePlayingState = EGamePlayingState::GameOver;
	//}
}