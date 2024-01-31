#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Framework/I_Weapon.h"
#include "C_Sword.generated.h"

UCLASS()
class U5_RPG_API AC_Sword : public AActor, public II_Weapon
{
	GENERATED_BODY()
private:
	AC_Sword();

protected:

public:
	static AC_Sword* Spawn(class ACharacter* InOwner);

public:
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void EquipSword();
	UFUNCTION(BlueprintCallable)
	void UnEquipSword();
};
