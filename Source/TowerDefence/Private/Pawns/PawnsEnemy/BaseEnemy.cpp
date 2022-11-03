// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/PawnsEnemy/BaseEnemy.h"

#include "Kismet/GameplayStatics.h"
#include "Pawns/Vehicle_M112.h"
#include "Projectile/BaseProjectile.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ABaseEnemy::OnCapsuleHit);
	CapsuleArm=CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleArm"));
	CapsuleArm->SetupAttachment(GetMesh(),TEXT("ArmHit"));
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ABaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurentHP-=DamageAmount;
	if(CurentHP<=0)
	{
		Destroy();
	}
	return DamageAmount;
}
