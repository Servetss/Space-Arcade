// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h" 
#include "ShootComponent.h"
#include "PlayerPawn.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDamagedEnded);

UCLASS()
class ARCADA_API APlayerPawn : public APawn
{
	GENERATED_BODY()

private:
	FVector2D TouchLocation;
	bool Touching;

	UMaterialInterface* PawnMaterial;


public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	bool CheckCanBeDamaged();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController * InstigatedBy, AActor * DamageCauser) override;

	FVector NewLocation;
	FVector2D TouchDeltaMove;
	FVector2D MoveLimit;

	void OnTouchPressed(ETouchIndex::Type Fingerindex, FVector Location);
	void OnTouchMove(ETouchIndex::Type Fingerindex, FVector Location);

	virtual void PossessedBy(AController* NewController)override;
	APlayerController* PlayerController;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Healths")
		bool CanBeDamaged();
		bool CanBeDamaged_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Healths")
		void RecoverPawn();
		void RecoverPawn_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Healths")
		void ExplodePawn();
		void ExplodePawn_Implementation();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Pawn")
	UBoxComponent* PawnCollision;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Pawn")
		UStaticMeshComponent* PawnMesh;
	

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Pawn")
	UCameraComponent* PawnCamera;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Controls")
		float TouchMoveSensivity;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Shooting")
		UShootComponent* ShootComponent;

	UPROPERTY(BlueprintAssignable, Category = "Healths")
		FPawnDamagedEnded PawnDamaged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
		UMaterialInterface* RecoverMaterial;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
		UParticleSystem* DestroyParticle;

};
