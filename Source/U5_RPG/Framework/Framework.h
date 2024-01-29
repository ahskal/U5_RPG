#pragma once
#include "CoreMinimal.h"

// 컴포넌트
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"


// 몽타주
#include "Animation/AnimMontage.h"


#include "Engine/LocalPlayer.h"
#include "Engine/SkeletalMesh.h"

#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "GameFramework/SpringArmComponent.h"

//카메라 컴포넌트
#include "Camera/CameraComponent.h"

// 향상된 입력
// Build.cs 헤더에
// PublicDependencyModuleNames.AddRange(new string[] { "EnhancedInput" } ) 추가해줘야된다.
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

#define CM CreateManager::

namespace CreateManager
{
	template <typename T>
	static T* GetComponent(AActor* InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}

	template<typename T>
	static T* GetComponent(AActor* InActor, FString InComponentName)
	{
		TArray<T*> components;
		InActor->GetComponents<T>(components);

		for (T* component : components)
		{
			if (component->GetName() == InComponentName)
				return component;
		}
		return NULL;
	}
	template<typename T>
	static void CreateComponent(AActor* Actor, T** Component, FName Name,
		USceneComponent* Parent = nullptr)
	{
		*Component = Actor->CreateDefaultSubobject<T>(Name);
		if (Parent) (*Component)->SetupAttachment(Parent);
		else Actor->SetRootComponent((*Component));
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString Path)
	{
		ConstructorHelpers::FClassFinder<T> asset(*Path);
		verifyf(asset.Succeeded(), L"Succeeded")
			* OutClass = asset.Class;
	}

	template<typename T>
	static void GetObject(T*& Asset, const FString& Path)
	{
		ConstructorHelpers::FObjectFinder<T> ObjectFinder(*Path);

		if (ObjectFinder.Succeeded()) Asset = ObjectFinder.Object;
		else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Asset: %s"), *Path);
	}

	template<typename T>
	static void GetAsset(T** AssetObject, FString Path)
	{
		ConstructorHelpers::FObjectFinder<T> Asset(*Path);
		verifyf(Asset.Succeeded(), L"Succeeded")
			* AssetObject = Asset.Object;
	}

	template<typename T>
	static void GetAssetDynamic(T** AssetObject, FString Path)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *Path));
		verifyf(obj, L"Succeeded")
			* AssetObject = obj;
	}

	template<typename T>
	static T* FindActor(UWorld* InWord)
	{
		for (AActor* actor : InWord->GetCurrentLevel()->Actors)
		{
			if (!!actor && actor->IsA<T>())
				return Cast<T>(actor);
		}
		return nullptr;
	}

	template<typename T>
	static void FindActors(UWorld* InWord, TArray<T*>& OutActors)
	{
		OutActors.Empty();

		for (AActor* actor : InWord->GetCurrentLevel()->Actors)
		{
			if (!!actor && actor->IsA<T>())
				OutActors.Add(Cast<T>(actor));
		}
	}
}

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"