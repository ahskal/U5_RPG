#pragma once

#include "CoreMinimal.h"
#include "../Framework/A_Weapon.h"
#include "C_Sword.generated.h"

UCLASS()
class U5_RPG_API AC_Sword : public AA_Weapon
{
	GENERATED_BODY()
public:
	static AC_Sword* Spawn(class ACharacter* InOwner);
public:
	AC_Sword();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void EquipSword();
	UFUNCTION(BlueprintCallable)
	void UnEquipSword();
};
