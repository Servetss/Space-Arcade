// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameHealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameHealthEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthsChangedEvent, int, ChangeValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADA_API UGameHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

	UPROPERTY(EditAnyWhere, Category = "GameHealth")
	int Healths;

	
public:	

	UFUNCTION(BlueprintCallable, Category = "GameHealth")
		void ChangeHealth(int ByValue);

	UFUNCTION(BlueprintPure, Category = "GameHealth")
		int GetHealths();
	
	UPROPERTY(BlueprintAssignable, Category = "GameHealth")
		FGameHealthEnded HealthsEnded;

	UPROPERTY(BlueprintAssignable, Category = "GameHealth")
		FHealthsChangedEvent HealthChangedEnded;
};
