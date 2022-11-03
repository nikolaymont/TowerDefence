// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawners/EnemySpawn.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PawnsEnemy/BaseEnemy.h"

// Sets default values
AEnemySpawn::AEnemySpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemySpawn::StartSpawnEnemy()
{
	SpawnIsActive = true;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("SpawnPoint"), FoundActors);
	TimerSpawn();
}

void AEnemySpawn::StopSpawnEnemy()
{
	SpawnIsActive = false;

	//UGameplayStatics::GetPlayerController(GetWorld(),0)->Possess(vehicle);-Попросит контроллер вселится в новую машину
	//После спавна и вселения в новую машину
	//UGameplayStatics::GetPlayerController(GetWorld(),0)->GetPawn()->Destroyed(); -удалит старую
}

void AEnemySpawn::SpawnProcess()
{
	if(FoundActors.Num()!=0)
	{
		if(a<=30)
		{
			int index = FMath::RandRange(0,FoundActors.Num()-1);
			ABaseEnemy* enemy = GetWorld()->SpawnActor<ABaseEnemy>(Enemy,FoundActors[index]
				->GetActorLocation(),FoundActors[index]->GetActorRotation());
			if(enemy!=nullptr)
			{
				//UGameplayStatics::GetPlayerController(GetWorld(),0)->Possess(enemy);
				enemy->TargetPlayer=Player;
				a++;
				TimerSpawn();
			}
		}
		
	}
	
	
}

void AEnemySpawn::TimerSpawn()
{
	if(SpawnIsActive)
	{
		FTimerHandle Handle;  
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "SpawnProcess");
	
		GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, 1, false);
	}
		
}

// Called when the game starts or when spawned
void AEnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> Players;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),TEXT("Player"),Players);
	if(Players[0]!=nullptr)
	{
		Player= Players[0];
	}
	
	StartSpawnEnemy();
}

// Called every frame
void AEnemySpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

