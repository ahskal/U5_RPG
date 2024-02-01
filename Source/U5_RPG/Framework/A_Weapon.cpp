#include "A_Weapon.h"
#include "Framework.h"

void AA_Weapon::Equip()
{
	UE_LOG(LogTemp, Log, TEXT("Equip"));
	OwnerCharacter->PlayAnimMontage(EquipMontage);
}


void AA_Weapon::UnEquip()
{
	UE_LOG(LogTemp, Log, TEXT("UnEquip"));
	OwnerCharacter->PlayAnimMontage(UnequipMontage);
}
