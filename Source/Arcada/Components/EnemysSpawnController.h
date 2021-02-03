// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Pawns/BasePawn.h"
#include "EnemysSpawnController.generated.h"


USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Enemies")
		TSubclassOf<ABasePawn> EnemyClass = ABasePawn::StaticClass(); 

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Enemies")
		FTransform SpawnTransform;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Enemies")
		int NumOfEnemies;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Enemies")
		float SpawnDelay;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADA_API UEnemysSpawnController : public UActorComponent
{
	GENERATED_BODY()


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void Deactivate() override;

	void StartSpawnStage();
	void SpawnEnemy();

	FEnemySpawnInfo SpawnStage;

	int EnemiesSpawned;

	FTimerHandle ChangeStagesTimer;
	FTimerHandle EnemySpawnTimer;

	FRandomStream Random;
public:


	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Enemies")
	TArray<FEnemySpawnInfo> SpawnStages;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Enemies")
	float StageMinDelay;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Enemies")
	float StageMaxDelay;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Enemies")
		float ChangeStageTimeMultiplier;

};
