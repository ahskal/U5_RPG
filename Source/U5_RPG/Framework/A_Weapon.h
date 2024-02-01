#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Weapon.generated.h"

UCLASS()
class U5_RPG_API AA_Weapon : public AActor
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
