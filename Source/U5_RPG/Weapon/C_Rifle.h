#pragma once

#include "CoreMinimal.h"
#include "../Framework/A_Weapon.h"
#include "C_Rifle.generated.h"

UCLASS()
class U5_RPG_API AC_Rifle : public AA_Weapon
{
	GENERATED_BODY()	
public:
	static AC_Rifle* Spawn(class ACharacter* InOwner);
public:	
	AC_Rifle();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void EquipRifle();
	UFUNCTION(BlueprintCallable)
	void UnEquipRifle();
};
