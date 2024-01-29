#pragma once

#include "CoreMinimal.h"
#include "../Framework/C_Weapon.h"
#include "C_Sword.generated.h"

UCLASS()
class U5_RPG_API AC_Sword : public AC_Weapon
{
	GENERATED_BODY()
private:
	AC_Sword();

protected:

public:
	static AC_Sword* Spawn(class ACharacter* InOwner);

	UFUNCTION(BlueprintCallable)
	void EquipSword();
	UFUNCTION(BlueprintCallable)
	void UnEquipSword();
};
