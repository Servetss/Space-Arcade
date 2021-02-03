// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/EnemysSpawnController.h"
#include "Components/GameHealthComponent.h"
#include "Components/ShapeComponent.h"
#include "ShootComponent.h"
#include "ArcadaGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);


USTRUCT(BlueprintType)
struct FShootInfoLevel
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Shooting")
		TArray<FShootInfo> ShootInfos;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Shooting")
		float ShootPeriod;

};


UCLASS()
class ARCADA_API AArcadaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public: 
	AArcadaGameModeBase();

	virtual void BeginPlay() override;


protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Game")
		void ExplodePawn();
		void ExplodePawn_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
		void RecoverPawn();
		void RecoverPawn_Implementation();

	FTimerHandle RecoverTimer;
	FTimerHandle IncreaseDifficultyTimer;

	bool IsGameOver;

public:

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Enemies")
		UEnemysSpawnController* EnemysSpawnController;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "GameHealth")
		UGameHealthComponent* HealthsComponent;

	UPROPERTY(BlueprintAssignable, Category = "Game")
		FGameOverEvent GameOver;

	
	UFUNCTION(BlueprintCallable, Category = "Game")
		void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
		void IncreaseDifficulty();

	UFUNCTION(BlueprintCallable, Category = "Game")
		void AddPoints(int Points); 

	UFUNCTION(BlueprintCallable, Category = "Game")
		bool ChangeShootLevel(bool Up);	

	UPROPERTY(BlueprintReadWrite, Category = "Game")
		float PlayerRecoverTime;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Game")
		float IncreaseDifficultyPeriod;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class APlayerPawn* PlayerPawn; // Писать class или подключать include

	UPROPERTY(BlueprintReadOnly, Category = "Game")
		int GamePoints;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Shooting")
	TArray<FShootInfoLevel> ShootInfoLevels;

	UPROPERTY(BlueprintReadOnly, Category = "Shooting")
		int CurrentShootLevels;

};
