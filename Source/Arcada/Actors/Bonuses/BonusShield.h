// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Bonuses/Bonus.h"
#include "BonusShield.generated.h"


class APawnShield;
/**
 * 
 */
UCLASS()
class ARCADA_API ABonusShield : public ABonus
{
	GENERATED_BODY()
	
	
protected:
	virtual void BonusCollected_Implementation() override;

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Shield")
		TSubclassOf<APawnShield> ShieldClass;


	
};
