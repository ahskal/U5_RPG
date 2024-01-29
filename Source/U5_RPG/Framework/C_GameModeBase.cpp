// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GameModeBase.h"

AC_GameModeBase::AC_GameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/Game/BP_C_Character.BP_C_Character_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
