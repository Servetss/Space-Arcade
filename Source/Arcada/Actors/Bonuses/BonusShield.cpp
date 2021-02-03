// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusShield.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"
#include "Engine/World.h"
#include "Actors/Other/PawnShield.h"

void ABonusShield::BonusCollected_Implementation()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Pawn) return;
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(Pawn);

	if (!PlayerPawn || !PlayerPawn->bCanBeDamaged) return;



	APawnShield* Shield = GetWorld()->SpawnActor<APawnShield>(ShieldClass);
	Shield->ActivateShield(PlayerPawn);

	Super::BonusCollected_Implementation();
}


