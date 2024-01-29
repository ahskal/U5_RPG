#pragma once

#include "CoreMinimal.h"
#include "../Framework/C_Weapon.h"
#include "C_Rifle.generated.h"

UCLASS()
class U5_RPG_API AC_Rifle : public AC_Weapon
{
	GENERATED_BODY()
	
public:	
	AC_Rifle();

protected:

public:	
	static AC_Rifle* Spawn(class ACharacter* InOwner);

	UFUNCTION(BlueprintCallable)
	void EquipRifle();
	UFUNCTION(BlueprintCallable)
	void UnEquipRifle();

};
