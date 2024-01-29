// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Character.h"
#include "Framework.h"
#include "../Weapon/C_Sword.h"
#include "../Weapon/C_Rifle.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

// Sets default values
AC_Character::AC_Character()
{
	// 틱마다 업데이트가 필요한경우 켜주면 된다.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌 캡슐 크기 설정
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 90.0f);

	// 컨트롤러가 회전할 때 회전하지 말고 카메라에 영향을 주도록 하세요.
	// 기본값은 1비트로 정의 된값을 0으로 초기화 -> true에서 false
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 이동 구성
	GetCharacterMovement()->bOrientRotationToMovement = true; // 입력방향 회전
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // 회전 속도

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CM CreateComponent<USpringArmComponent>(this, &SpringArm, TEXT("SpringArm"), GetCapsuleComponent());
	SpringArm->TargetArmLength = 300.0f;
	// 캐릭터 회전에 카메라가 따라가는가
	SpringArm->bUsePawnControlRotation = true;

	SpringArm->SetRelativeLocation(FVector(20, 0, 45));
	SpringArm->SetRelativeRotation(FRotator(-20, 0, 0));

	CM CreateComponent<UCameraComponent>(this, &Camera, TEXT("Camera"), SpringArm);
	// 캐릭터 회전에 카메라가 따라가는가
	Camera->bUsePawnControlRotation = false;

	FString MeshPath = TEXT("/Script/Engine.SkeletalMesh'/Game/Character/Dhana/Meshs/Dhana.Dhana'");
	CM GetAsset<USkeletalMesh>(&MeshAsset, MeshPath);
	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Animation
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	FString AnimBlueprintPath = TEXT("/Script/Engine.AnimBlueprint'/Game/Game/ABP_C_AnimInstance.ABP_C_AnimInstance'");
	CM GetObject<UAnimBlueprint>(AnimBlueprintAsset, AnimBlueprintPath);
	GetMesh()->SetAnimInstanceClass(AnimBlueprintAsset->GeneratedClass);

	FString ImcPath = TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Game/Input/IMC_Default.IMC_Default'");
	CM GetObject<UInputMappingContext>(DefaultMappingContext, ImcPath);

	FString MoveActionPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Game/Input/Actions/IA_Move.IA_Move'");
	CM GetObject<UInputAction>(MoveAction, MoveActionPath);

	FString JumpActionPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Game/Input/Actions/IA_Jump.IA_Jump'");
	CM GetObject<UInputAction>(JumpAction, JumpActionPath);

	FString LookActionPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Game/Input/Actions/IA_Look.IA_Look'");
	CM GetObject<UInputAction>(LookAction, LookActionPath);

	FString WalkSlowActionPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Game/Input/Actions/IA_WalkSlow.IA_WalkSlow'");
	CM GetObject<UInputAction>(WalkSlowAction, WalkSlowActionPath);

	FString WalkFastActionPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Game/Input/Actions/IA_WalkFast.IA_WalkFast'");
	CM GetObject<UInputAction>(WalkFastAction, WalkFastActionPath);

	FString P1ActionPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Game/Input/Actions/IA_P1.IA_P1'");
	CM GetObject<UInputAction>(P1Action, P1ActionPath);

	FString P2ActionPath = TEXT("/Script/EnhancedInput.InputAction'/Game/Game/Input/Actions/IA_P2.IA_P2'");
	CM GetObject<UInputAction>(P2Action, P2ActionPath);
}
// Called every frame
void AC_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void AC_Character::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem
			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	// Spawn Sword
	Sword = AC_Sword::Spawn(this);
	Rifle = AC_Sword::Spawn(this);
}

// Called to bind functionality to input
void AC_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent) {
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AC_Character::Move);

		// Walk Slow
		EnhancedInputComponent->BindAction(WalkSlowAction, ETriggerEvent::Started, this, &AC_Character::WalkSlow);
		EnhancedInputComponent->BindAction(WalkSlowAction, ETriggerEvent::Completed, this, &AC_Character::WalkDefault);

		// Walk Fast
		EnhancedInputComponent->BindAction(WalkFastAction, ETriggerEvent::Started, this, &AC_Character::WalkFast);
		EnhancedInputComponent->BindAction(WalkFastAction, ETriggerEvent::Completed, this, &AC_Character::WalkDefault);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AC_Character::Look);

		// P1 (Sword)
		EnhancedInputComponent->BindAction(P1Action, ETriggerEvent::Started, this, &AC_Character::EquipSword);

		// P2 (Rifle)
		EnhancedInputComponent->BindAction(P2Action, ETriggerEvent::Started, this, &AC_Character::EquipRifle);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AC_Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AC_Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	//UE_LOG(LogTemp, Warning, TEXT("Look called: X=%f, Y=%f"), LookAxisVector.X, LookAxisVector.Y);

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AC_Character::WalkSlow(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}

void AC_Character::WalkDefault(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void AC_Character::WalkFast(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void AC_Character::EquipSword()
{
	if (PlayerWeapon == EPlayerWeapon::Unarmed){
		Sword->Equip();
		PlayerWeapon = EPlayerWeapon::Sword;
	}
	else {
		UnEquip();
	}
}

void AC_Character::EquipRifle()
{
	if (PlayerWeapon == EPlayerWeapon::Unarmed)
	{
		Rifle->Equip();
		PlayerWeapon = EPlayerWeapon::Rifle;
	}
	else {
		UnEquip();
	}
}

void AC_Character::UnEquip()
{
	switch (PlayerWeapon) {
	case EPlayerWeapon::Rifle: Rifle->UnEquip(); break;
	case EPlayerWeapon::Sword: Sword->UnEquip(); break;
	}
}

void AC_Character::Attack()
{
}
