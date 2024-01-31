// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Framework/I_Unit.h"
#include "C_Enemy.generated.h"

UCLASS()
class U5_RPG_API AC_Enemy : public ACharacter , public II_Unit
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
