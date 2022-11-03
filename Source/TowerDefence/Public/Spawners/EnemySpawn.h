// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawn.generated.h"

UCLASS()
class TOWERDEFENCE_API AEnemySpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UClass* Enemy;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> FoundActors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int a =0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
	AActor* Player;

	bool SpawnIsActive = false;
	
	void StartSpawnEnemy();

	void StopSpawnEnemy();
	
    UFUNCTION()
	void SpawnProcess();
	
	void TimerSpawn();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
