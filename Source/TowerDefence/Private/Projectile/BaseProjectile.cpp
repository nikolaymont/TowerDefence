// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BaseProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "Pawns/Vehicle_M112.h"
#include "Pawns/PawnsEnemy/BaseEnemy.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject< UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	MeshComponent = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MovementComponent = CreateDefaultSubobject< UProjectileMovementComponent>(TEXT("MovementComponent"));
	Capsule->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnCapsuleHit);
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::OnCapsuleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor !=nullptr)
	{
		ABaseEnemy* enemy = Cast<ABaseEnemy>(OtherActor);
		if(enemy !=nullptr&&GetInstigator()->GetController())
		{
			UGameplayStatics::ApplyDamage(OtherActor,10.f,
		GetInstigator()->GetController(),this,UDamageType::StaticClass());
		}
	}	
}


