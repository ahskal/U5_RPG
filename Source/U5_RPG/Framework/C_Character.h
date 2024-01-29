// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "C_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USkeletalMesh;
class UAnimBlueprint;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UENUM(BlueprintType)
enum class EPlayerWeapon : uint8
{
	Unarmed, Sword, Rifle
};

class AC_Sword;
class AC_Rifle;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class U5_RPG_API AC_Character : public ACharacter
{
	GENERATED_BODY()
private:
	AC_Sword* Sword = nullptr;
	AC_Rifle* Rifle = nullptr;

public:
	// Sets default values for this character's properties
	AC_Character();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** WalkSlow Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* WalkSlowAction;

	/** WalkFast Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* WalkFastAction;

	/** P1Action Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* P1Action;

	/** P2Action Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* P2Action;

	// SpringArm
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class USpringArmComponent* SpringArm;

	// Camera
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	class UCameraComponent* Camera;

	// SkeletalMesh 
	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* MeshAsset;

	// ABP
	UPROPERTY(EditDefaultsOnly)
	UAnimBlueprint* AnimBlueprintAsset;

	UPROPERTY(EditDefaultsOnly)
	EPlayerWeapon PlayerWeapon{ EPlayerWeapon::Unarmed };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void WalkSlow(const FInputActionValue& Value);
	void WalkDefault(const FInputActionValue& Value);
	void WalkFast(const FInputActionValue& Value);

	void EquipSword();
	void EquipRifle();
	void UnEquip();

	void Attack();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns FollowCamera subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return SpringArm; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return Camera; }

	//UFUNCTION(BlueprintCallable)
	//FORCEINLINE class AC_Sword* GetSword() { return Sword; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EPlayerWeapon GetPlayerWeaponState() const { return PlayerWeapon; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE class AC_Sword* GetSword() { return Sword; };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE class AC_Rifle* GetRifle() { return Rifle; };
};