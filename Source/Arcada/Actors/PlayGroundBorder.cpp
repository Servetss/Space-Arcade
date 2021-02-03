// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayGroundBorder.h"
#include "Components/BoxComponent.h"
#include "Pawns/PlayerPawn.h"

// Sets default values
APlayGroundBorder::APlayGroundBorder()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);

	Trigger->SetCollisionProfileName("OverlapAll");
}

void APlayGroundBorder::NotifyActorEndOverlap(AActor * OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	if(!OtherActor) return;
	if (Cast<APlayerPawn>(OtherActor)) return;

	//UE_LOG(LogTemp, Log, TEXT("OUT OF PLAYGROUND: %s"), *OtherActor->GetName());

	OtherActor->Destroy();
}
