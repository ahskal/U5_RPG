#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "A_Unit.generated.h"

class USkeletalMesh;
class AC_Sword;
class AC_Rifle;

UCLASS()
class U5_RPG_API AA_Unit : public ACharacter
{
	GENERATED_BODY()
protected:
	class AC_Sword* Sword = nullptr;
	class AC_Rifle* Rifle = nullptr;
	bool canRotate = false;
	bool canMove = true;

public:
	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* MeshAsset = nullptr;
protected:


public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE class AC_Sword* GetSword() { return Sword; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE class AC_Rifle* GetRifle() { return Rifle; };

	//UFUNCTION(BlueprintCallable)
	//FORCEINLINE class AC_Sword* GetSword() { return Sword; };
};
