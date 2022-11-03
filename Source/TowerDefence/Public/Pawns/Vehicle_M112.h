// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Vehicle_M112.generated.h"

class AEnemySpawn;
UCLASS()
class TOWERDEFENCE_API AVehicle_M112 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVehicle_M112();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBoxComponent* Box;
	
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Components")
	USceneComponent* Muzzle;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UClass* Projectile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> FoundEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCamera;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	float CountShootInMinutes ;

	bool LeftMousePressed = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Shoot();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)override;
	
	void MousePressed();
	
	void MouseReleased();
	
	void ShootTimer();

	void DeleteAllEnemy();

	void DestroyVehicle();
};
     