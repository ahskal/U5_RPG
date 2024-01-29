// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Weapon.generated.h"


class USkeletalMeshComponent;
class USceneComponent;

UCLASS()
class U5_RPG_API AC_Weapon : public AActor
{
	GENERATED_BODY()
protected:
	class ACharacter* OwnerCharacter;

	int32	AttackCurStage;
	int32	AttackMaxStage;
	float	ComboTime;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* SkeletalMesh;

	
public:	
	// Sets default values for this actor's properties
	AC_Weapon();

	// attack montages
	UPROPERTY(EditAnywhere, Category = "Anim")
	UAnimMontage* AttackMontage;

	// equip montages
	UPROPERTY(EditAnywhere, Category = "Anim")
	UAnimMontage* EquipMontage;

	// unequip montages
	UPROPERTY(EditAnywhere, Category = "Anim")
	UAnimMontage* UnequipMontage;

	UPROPERTY(EditAnywhere)
	FName HandSocket{ TEXT("HandSocket") };

	UPROPERTY(EditAnywhere)
	FName SheathSocket{ TEXT("SheathSocket") };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Equip();
	void UnEquip();
};
