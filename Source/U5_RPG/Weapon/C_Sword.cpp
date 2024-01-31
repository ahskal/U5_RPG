#include "C_Sword.h"
#include "../Framework/Framework.h"

AC_Sword::AC_Sword()
{
	PrimaryActorTick.bCanEverTick = true;

	OwnerCharacter = nullptr;
	HandSocket = { TEXT("HandSocket") };
	SheathSocket = { TEXT("SheathSocket") };

	PrimaryActorTick.bCanEverTick = true;
	CM CreateComponent(this, &Root, TEXT("Root"));
	CM CreateComponent(this, &SkeletalMeshComponent, "Mesh", Root);


	FString SkeletalMeshPath = TEXT("/Script/Engine.SkeletalMesh'/Game/Weapon/Sword/Sword.Sword'");
	CM GetObject<USkeletalMesh>(SkeletalMesh, SkeletalMeshPath);
	SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);

	FString EquipMontagePath = TEXT("/Script/Engine.AnimMontage'/Game/Character/Dhana/Animation/Equip/AM_Draw_Sword.AM_Draw_Sword'");
	CM GetObject<UAnimMontage>(EquipMontage, EquipMontagePath);

	// unequip montages
	FString UnequipMontagePath = TEXT("/Script/Engine.AnimMontage'/Game/Character/Dhana/Animation/Equip/AM_Sheath_Sword.AM_Sheath_Sword'");
	CM GetObject<UAnimMontage>(UnequipMontage, UnequipMontagePath);
}

void AC_Sword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

AC_Sword* AC_Sword::Spawn(ACharacter* InOwner)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = InOwner;
	SpawnParams.Instigator = InOwner->GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = InOwner->GetActorLocation();
	FRotator SpawnRotation = InOwner->GetActorRotation();

	AC_Sword* Sword = InOwner->GetWorld()->SpawnActor<AC_Sword>(AC_Sword::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
	Sword->AttachToComponent(InOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Sword->SheathSocket);

	return Sword;
}

void AC_Sword::EquipSword()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocket);
}

void AC_Sword::UnEquipSword()
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SheathSocket);
}
