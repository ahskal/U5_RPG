// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../Framework/Framework.h"

// Sets default values
AC_Bullet::AC_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Bullet::Fire(FVector Pos, FVector Dir)
{
	UProjectileMovementComponent* projectile =
		CM GetComponent<UProjectileMovementComponent>(this);
	if (projectile == nullptr) return;

	SetActorLocation(Pos);
	projectile->Velocity = Dir * projectile->InitialSpeed;
}

