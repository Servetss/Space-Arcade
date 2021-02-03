// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"


// Sets default values for this component's properties
UGameHealthComponent::UGameHealthComponent() : Healths(3)
{
}


// Called when the game starts
void UGameHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player Pawn!!!!!"));
		return;
	}

	//
}




void UGameHealthComponent::ChangeHealth(int ByValue)
{
	Healths += ByValue;

	HealthChangedEnded.Broadcast(ByValue);
	if (Healths <= 0)
	{
		HealthsEnded.Broadcast();
	}
}

int UGameHealthComponent::GetHealths()
{
	return Healths;
}
