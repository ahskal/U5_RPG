// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class U5_RPG_API UC_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	class AC_Character* Owner = nullptr;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	IsAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bIsMove = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector	Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator Rotator;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int		PlayerWeaponState;
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
