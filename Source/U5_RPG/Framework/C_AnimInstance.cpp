// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AnimInstance.h"
#include "../Framework/Framework.h"
#include "../Framework/C_Character.h"

void UC_AnimInstance::NativeBeginPlay()
{
	Owner = Cast<AC_Character>(TryGetPawnOwner());
}

void UC_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Owner == nullptr) return;

	Speed = Owner->GetVelocity().Size2D();
	if (Speed) {
		bIsMove = true;
	}
	else {
		bIsMove = false;
	}
	IsAir = Owner->GetCharacterMovement()->IsFalling();
	Velocity = Owner->GetVelocity();
	FRotator rotator = Owner->GetActorRotation();
	Velocity = UKismetMathLibrary::InverseTransformDirection(FTransform(rotator), Velocity);

	PlayerWeaponState = (int)(Owner->GetPlayerWeaponState());
}
