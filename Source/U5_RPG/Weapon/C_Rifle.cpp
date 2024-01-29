#include "C_Rifle.h"
#include "../Framework/Framework.h"

AC_Rifle::AC_Rifle()
{
	PrimaryActorTick.bCanEverTick = true;

	OwnerCharacter = nullptr;

	//FString SkeletalMeshPath = TEXT("/Script/Engine.SkeletalMesh'/Game/Weapon/Sword/Sword.Sword'");
	//CM GetObject<USkeletalMesh>(SkeletalMesh, SkeletalMeshPath);
	//SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
	//
	//FString EquipMontagePath = TEXT("/Script/Engine.AnimMontage'/Game/Character/Dhana/Animation/Equip/AM_Draw_Sword.AM_Draw_Sword'");
	//CM GetObject<UAnimMontage>(EquipMontage, EquipMontagePath);
	//
	//// unequip montages
	//FString UnequipMontagePath = TEXT("/Script/Engine.AnimMontage'/Game/Character/Dhana/Animation/Equip/AM_Sheath_Sword.AM_Sheath_Sword'");
	//CM GetObject<UAnimMontage>(UnequipMontage, UnequipMontagePath);
}

AC_Rifle* AC_Rifle::Spawn(ACharacter* InOwner)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = InOwner;
	SpawnParams.Instigator = InOwner->GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = InOwner->GetActorLocation();
	FRotator SpawnRotation = InOwner->GetActorRotation();

	AC_Rifle* Rifle = InOwner->GetWorld()->SpawnActor<AC_Rifle>(AC_Rifle::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	Rifle->AttachToComponent(InOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Rifle->SheathSocket);

	return Rifle;
}

void AC_Rifle::EquipRifle()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocket);
}

void AC_Rifle::UnEquipRifle()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SheathSocket);
}


