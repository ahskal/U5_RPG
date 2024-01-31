// Fill out your copyright notice in the Description page of Project Settings.


#include "I_Weapon.h"
#include "../Framework/Framework.h"

void II_Weapon::Equip()
{
	UE_LOG(LogTemp, Log, TEXT("Equip"));
	OwnerCharacter->PlayAnimMontage(EquipMontage);
}

void II_Weapon::UnEquip()
{
	UE_LOG(LogTemp, Log, TEXT("UnEquip"));
	OwnerCharacter->PlayAnimMontage(UnequipMontage);
}
