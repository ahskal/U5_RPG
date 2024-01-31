#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Framework/I_Weapon.h"
#include "C_Rifle.generated.h"

UCLASS()
class U5_RPG_API AC_Rifle : public AActor , public II_Weapon
{
	GENERATED_BODY()	
public:	
	AC_Rifle();

protected:
public:	
	static AC_Rifle* Spawn(class ACharacter* InOwner);
public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void EquipRifle();
	UFUNCTION(BlueprintCallable)
	void UnEquipRifle();
};
