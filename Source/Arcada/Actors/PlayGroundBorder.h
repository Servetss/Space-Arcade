// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayGroundBorder.generated.h"


UCLASS()
class ARCADA_API APlayGroundBorder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayGroundBorder();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	class UBoxComponent* Trigger;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
