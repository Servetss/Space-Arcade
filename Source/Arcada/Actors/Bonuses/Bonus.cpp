// Fill out your copyright notice in the Description page of Project Settings.

#include "Bonus.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Pawns/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABonus::ABonus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));
	RootComponent = Collision;

	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	//Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	//Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); 

	Collision->SetSphereRadius(30);
}


void ABonus::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);


	if (!OtherActor)return;
	if (!Cast<APlayerPawn>(OtherActor))return;

	BonusCollected();

}

void ABonus::BonusCollected_Implementation()
{
	if (CollectParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectParticle, GetActorTransform(), true);

	Destroy();
}

// Called every frame
void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float WorldMoveOffset = -200.f * DeltaTime;
	AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));

}

