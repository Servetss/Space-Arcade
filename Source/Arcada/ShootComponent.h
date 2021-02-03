// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/ProjectTiles/ShootProjectile.h" 
#include "ShootComponent.generated.h"


USTRUCT(BlueprintType)
struct FShootInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Shooting")
		TSubclassOf<AShootProjectile> ProjectileClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Shooting")
		float Damage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Shooting")
		FVector Offset;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Shooting")
		float Angle;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADA_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



	void Shoot();
	FTimerHandle ShootingTimer;

public:
	UFUNCTION(BlueprintCallable, Category = "Shooting")
		void StartShooting(); 

	UFUNCTION(BlueprintCallable, Category = "Shooting")
		void StopShooting();

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Shooting")
		float ShootPeriod;	

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Shooting")
		TArray<FShootInfo> ShootInfos;
};
