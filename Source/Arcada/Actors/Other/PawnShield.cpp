// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnShield.h"
#include "Pawns/PlayerPawn.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
APawnShield::APawnShield() : ShieldTime(5.f)
{

}

void APawnShield::ActivateShield(APlayerPawn * PlayerPawn)
{
	if (!PlayerPawn) { Destroy();  return; }

	ShieldForPawn = PlayerPawn;

	ShieldForPawn->bCanBeDamaged = false;

	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget, //Координаты
		EAttachmentRule::SnapToTarget, // Поворот
		EAttachmentRule::KeepWorld,    // Размер
		false);						   // Физика (Вроде)

	AttachToActor(PlayerPawn, AttachRules); // Присоеденить один актор к другому (Обьект к торому присоединятся, объект настройки присойденения(атачмента))

	GetWorld()->GetTimerManager().SetTimer(ShieldTimer, this, &APawnShield::DeactivateShield,ShieldTime, false);

}

void APawnShield::DeactivateShield()
{
	if (!ShieldForPawn)return;
	ShieldForPawn->bCanBeDamaged = true;

	Destroy();
}
