// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Vehicle_M112.h"

#include "Kismet/GameplayStatics.h"
#include "Pawns/PawnsEnemy/BaseEnemy.h"
#include "Projectile/BaseProjectile.h"
#include "Spawners/EnemySpawn.h"

// Sets default values
AVehicle_M112::AVehicle_M112()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
 	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent=Box;
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(SkeletalMesh,TEXT("gun_jntSocket"));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; 
	CameraBoom->bUsePawnControlRotation = true;
	
	FirstPersonCamera = CreateDefaultSubobject< UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void AVehicle_M112::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVehicle_M112::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVehicle_M112::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AVehicle_M112::MousePressed);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AVehicle_M112::MouseReleased);
}

void AVehicle_M112::Shoot()
{
	ABaseProjectile* projectile =  GetWorld()->SpawnActor<ABaseProjectile>(Projectile,
			Muzzle->GetComponentLocation(), Muzzle->GetComponentRotation());
	projectile->SetInstigator(this);
	ShootTimer();
}

float AVehicle_M112::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
  AController* EventInstigator, AActor* DamageCauser)
{
	CurentHP = CurentHP -DamageAmount;
	if(CurentHP<=0)
	{
		TArray<AActor*> SpawnersEnemy;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("SpawnerEnemy"), SpawnersEnemy);
		if(SpawnersEnemy.Num()!=0)
		{
			Cast<AEnemySpawn>(SpawnersEnemy[0])->StopSpawnEnemy();
		}
		DeleteAllEnemy();
		AVehicle_M112* Vehicle = GetWorld()->SpawnActor<AVehicle_M112>(this->GetClass(),
			FVector(-1150,0-610,115.223785),FRotator(0,0,0));
		if(Vehicle!=nullptr)
		{
			GetController()->Possess(Vehicle);	
		}
		DestroyVehicle();
		//Cast<AEnemySpawn>(SpawnersEnemy[0])->StartSpawnEnemy();
	}
	return DamageAmount;
}

void AVehicle_M112::MousePressed()
{
	LeftMousePressed = true;
		ShootTimer();
}

void AVehicle_M112::MouseReleased()
{
	LeftMousePressed = false;
}

void AVehicle_M112::ShootTimer()
{
	if(LeftMousePressed == true)
	{
		FTimerHandle Handle;  
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "Shoot");
	
		GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, 60/CountShootInMinutes, false);
	}
}

void AVehicle_M112::DeleteAllEnemy()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Enemy"), FoundEnemy);
	
		for (auto Enemy : FoundEnemy)
		{
			Enemy->Destroy();
		}
}

void AVehicle_M112::DestroyVehicle()
{
	Destroy();
}



	

