// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Unit.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_Unit : public UInterface
{
	GENERATED_BODY()
};

class U5_RPG_API II_Unit
{
	GENERATED_BODY()
protected:
	class AC_Sword* Sword = nullptr;
	class AC_Rifle* Rifle = nullptr;
	bool canRotate = false;
	bool canMove = true;

public:
	// SkeletalMesh 

	//UPROPERTY(EditDefaultsOnly)
	//UPROPERTY(EditAnywhere)
	USkeletalMesh* MeshAsset;

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class AC_Sword* GetSword();
	virtual class AC_Sword* GetSword_Implementation() { return Sword; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class AC_Rifle* GetRifle();
	virtual class AC_Rifle* GetRifle_Implementation() { return Rifle; }


};
