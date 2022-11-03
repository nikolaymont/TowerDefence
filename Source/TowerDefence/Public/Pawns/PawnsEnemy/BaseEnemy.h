// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "BaseEnemy.generated.h"

UCLASS()
class TOWERDEFENCE_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseEnemy();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Params")
	float MaxHP;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Params")
	float CurentHP;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	UCapsuleComponent* CapsuleArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
	AActor* TargetPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
	float PowerOfDamage =10;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};
