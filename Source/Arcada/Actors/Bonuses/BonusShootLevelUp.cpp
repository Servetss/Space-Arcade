// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusShootLevelUp.h"
#include "Kismet/GameplayStatics.h"
#include "ArcadaGameModeBase.h"

void ABonusShootLevelUp::BonusCollected_Implementation()
{

	AArcadaGameModeBase* GameMode = Cast<AArcadaGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;

	GameMode->ChangeShootLevel(true);

	Super::BonusCollected_Implementation();
}


