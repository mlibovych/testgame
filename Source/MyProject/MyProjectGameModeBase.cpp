// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectGameModeBase.h"

#include "BaseHUD.h"
#include "Player/SGBasePlayerController.h"
#include "Player/SGBaseCharacter.h"

AMyProjectGameModeBase::AMyProjectGameModeBase()
{
	DefaultPawnClass = ASGBaseCharacter::StaticClass();
	PlayerControllerClass = ASGBasePlayerController::StaticClass();
	HUDClass = ABaseHUD::StaticClass();
}