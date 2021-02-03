// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemysSpawnController.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Called when the game starts
void UEnemysSpawnController::BeginPlay()
{
	Super::BeginPlay();

	Random.GenerateNewSeed();
	StartSpawnStage();
	
};

void UEnemysSpawnController::StartSpawnStage()
{
	SpawnStage = SpawnStages[Random.RandRange(0,SpawnStages.Num()-1)];
	EnemiesSpawned = 0;


	SpawnEnemy();
	float ChangeStageTime = Random.RandRange(StageMinDelay, StageMaxDelay) * ChangeStageTimeMultiplier;

	GetWorld()->GetTimerManager().SetTimer(ChangeStagesTimer, this, &UEnemysSpawnController::StartSpawnStage, ChangeStageTime, true);

}

void UEnemysSpawnController::SpawnEnemy()
{
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<ABasePawn>(SpawnStage.EnemyClass, SpawnStage.SpawnTransform,  SpawnParameters);

	EnemiesSpawned++;
	if (EnemiesSpawned < SpawnStage.NumOfEnemies)
	{
		GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, this, &UEnemysSpawnController::SpawnEnemy, SpawnStage.SpawnDelay, false);
	}
}

void UEnemysSpawnController::Deactivate()
{
	Super::Deactivate();
	GetWorld()->GetTimerManager().ClearTimer(ChangeStagesTimer);
	GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
}
