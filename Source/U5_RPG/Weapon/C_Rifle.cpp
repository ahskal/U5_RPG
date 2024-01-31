#include "C_Rifle.h"
#include "../Framework/Framework.h"

AC_Rifle::AC_Rifle()
{
	PrimaryActorTick.bCanEverTick = true;

	OwnerCharacter = nullptr;
	HandSocket = { TEXT("GunHandSocket") };
	SheathSocket = { TEXT("GunSocket") };

	PrimaryActorTick.bCanEverTick = true;
	CM CreateComponent(this, &Root, TEXT("Root"));
	CM CreateComponent(this, &SkeletalMeshComponent, "Mesh", Root);

	FString SkeletalMeshPath = TEXT("/Script/Engine.SkeletalMesh'/Game/Weapon/FPWeapon/Mesh/SK_FPGun.SK_FPGun'");
	CM GetObject<USkeletalMesh>(SkeletalMesh, SkeletalMeshPath);
	SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
	
	FString EquipMontagePath = TEXT("/Script/Engine.AnimMontage'/Game/Character/Dhana/Animation/Rifle/AM_Equip_Rifle.AM_Equip_Rifle'");
	CM GetObject<UAnimMontage>(EquipMontage, EquipMontagePath);
	
	// unequip montages
	FString UnequipMontagePath = TEXT("/Script/Engine.AnimMontage'/Game/Character/Dhana/Animation/Rifle/AM_UnEquip_Rifle.AM_UnEquip_Rifle'");
	CM GetObject<UAnimMontage>(UnequipMontage, UnequipMontagePath);
}

void AC_Rifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OwnerCharacter = Cast<ACharacter>(GetOwner());
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
