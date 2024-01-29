// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Weapon.h"
#include "../Framework/Framework.h"

// Sets default values
AC_Weapon::AC_Weapon()	:
	OwnerCharacter(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CM CreateComponent(this, &Root, TEXT("Root"));
	CM CreateComponent(this, &SkeletalMeshComponent, "Mesh", Root);
}

// Called when the game starts or when spawned
void AC_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void AC_Weapon::Equip()
{
	UE_LOG(LogTemp, Log, TEXT("Equip"));
	OwnerCharacter->PlayAnimMontage(EquipMontage);
}

void AC_Weapon::UnEquip()
{
	UE_LOG(LogTemp, Log, TEXT("UnEquip"));
	OwnerCharacter->PlayAnimMontage(UnequipMontage);
}

