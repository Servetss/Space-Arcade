// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusPoints.h"
#include "Kismet/GameplayStatics.h"
#include "ArcadaGameModeBase.h"

void ABonusPoints::BonusCollected_Implementation()
{

	AArcadaGameModeBase* GameMode = Cast<AArcadaGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode) GameMode->AddPoints(Points);

	Super::BonusCollected_Implementation();
}


