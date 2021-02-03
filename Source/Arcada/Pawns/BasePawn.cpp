// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/HealthComponent.h"
#include "ArcadaGameModeBase.h"
#include "Engine/World.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollison"));
	RootComponent = PawnCollision;
	PawnCollision->SetCollisionProfileName("Pawn");


	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(PawnCollision, NAME_None);
	PawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComponent->OnHealthEnded.AddDynamic(this, &ABasePawn::KillPawn);

	OnActorBeginOverlap.AddDynamic(this, &ABasePawn::OnEnemyOverlap);
}

void ABasePawn::KillPawn()
{
	AArcadaGameModeBase* GameMode = Cast<AArcadaGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode) GameMode->AddPoints(DestroyPont);

	SpawnBonuses();

	DestroyPawn();
}


void ABasePawn::DestroyPawn()
{
	if (DestroyParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);
	Destroy();
}

void ABasePawn::OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
	//UE_LOG(LogTemp,Log, TEXT("%s"), *OtherActor->GetName());
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0)) return;
	float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(), this, UDamageType::StaticClass());

	if(AppliedDamage > 0.f) DestroyPawn();
}

void ABasePawn::SpawnBonuses()
{
	FRandomStream Random;
	Random.GenerateNewSeed();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	for (FBonusChange Bonus : PossibleBonuses)
	{
		float RandChance = Random.RandRange(0.f,100.f);
		//UE_LOG(LogTemp, Log, TEXT("Chance: %d"), RandChance);
		if (RandChance < Bonus.Chance)
		{
			GetWorld()->SpawnActor<ABonus>(Bonus.BonusClass, GetActorLocation(), FRotator(0.f), SpawnParameters);
			//UE_LOG(LogTemp, Log, TEXT("BONUS!!!!!!!!!!!!!"));
		}
	}
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
		Super::Tick(DeltaTime);

		float WorldMoveOffset = -200.f * DeltaTime;
		AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));

}