// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Bonus.generated.h"

UCLASS(Blueprintable)
class ARCADA_API ABonus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonus();

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;
	
	UFUNCTION(BlueprintNativeEvent)
		void BonusCollected();
		virtual void BonusCollected_Implementation();

		virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Shooting")
		class USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
		UParticleSystem* CollectParticle;

};
