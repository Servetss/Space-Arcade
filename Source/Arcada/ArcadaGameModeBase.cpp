// Fill out your copyright notice in the Description page of Project Settings.

#include "ArcadaGameModeBase.h"
#include "Engine/World.h"
#include "TimerManager.h" 
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"


AArcadaGameModeBase::AArcadaGameModeBase() : PlayerRecoverTime(3), CurrentShootLevels(-1), IncreaseDifficultyPeriod(4.f)
{
	EnemysSpawnController = CreateDefaultSubobject<UEnemysSpawnController>(TEXT("EnemysSpawnController"));
	HealthsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));
}

void AArcadaGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HealthsComponent->HealthsEnded.AddDynamic(this, &AArcadaGameModeBase::EndGame);

	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (!PlayerPawn) return;
	ChangeShootLevel(true);

	PlayerPawn->PawnDamaged.AddDynamic(this, &AArcadaGameModeBase::ExplodePawn);

	GetWorld()->GetTimerManager().SetTimer(IncreaseDifficultyTimer, this, &AArcadaGameModeBase::IncreaseDifficulty, IncreaseDifficultyPeriod, true);
}

void AArcadaGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();
	HealthsComponent->ChangeHealth(-1);

	ChangeShootLevel(false);

	if(!IsGameOver)
		GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AArcadaGameModeBase::RecoverPawn, PlayerRecoverTime, false);
}

void AArcadaGameModeBase::RecoverPawn_Implementation()
{
	PlayerPawn->RecoverPawn();
}


void AArcadaGameModeBase::EndGame()
{
	IsGameOver = true;

	EnemysSpawnController->SetActive(false);	
	GameOver.Broadcast();

	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();

	UE_LOG(LogTemp, Log, TEXT("GAME OVER!!!!"));

	SetPause(UGameplayStatics::GetPlayerController(this, 0), false);
}

void AArcadaGameModeBase::IncreaseDifficulty()
{
	EnemysSpawnController->ChangeStageTimeMultiplier = FMath::Max(EnemysSpawnController->ChangeStageTimeMultiplier * 0.95f, 0.4f);
}

void AArcadaGameModeBase::AddPoints(int Points)
{
	GamePoints += Points;
}

bool AArcadaGameModeBase::ChangeShootLevel(bool Up)
{
	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn)return false;

	int NewLevel = FMath::Clamp(CurrentShootLevels + (Up ? 1 : -1), 0, ShootInfoLevels.Num()-1);

	if (NewLevel == CurrentShootLevels) return false;

	CurrentShootLevels = NewLevel; 

	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevels].ShootInfos;
	PlayerPawn->ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevels].ShootPeriod;

	return true;
}
