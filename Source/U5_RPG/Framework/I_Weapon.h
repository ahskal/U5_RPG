// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Weapon.generated.h"

class USkeletalMeshComponent;
class USceneComponent;

UINTERFACE(Blueprintable, MinimalAPI)
class UI_Weapon : public UInterface
{
	GENERATED_BODY()

};

class U5_RPG_API II_Weapon
{
	GENERATED_BODY()
protected:
	class ACharacter* OwnerCharacter;

	int32	AttackCurStage;
	int32	AttackMaxStage;
	float	ComboTime;

	USceneComponent* Root;

	USkeletalMeshComponent* SkeletalMeshComponent;

	USkeletalMesh* SkeletalMesh;
public:
	// attack montages	
	UAnimMontage* AttackMontage;

	// equip montages
	UAnimMontage* EquipMontage;

	// unequip montages
	UAnimMontage* UnequipMontage;

	FName HandSocket;
	FName SheathSocket;
public:

	void Equip();
	void UnEquip();
};
