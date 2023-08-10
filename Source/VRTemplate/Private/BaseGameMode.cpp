// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameMode.h"
#include "BasePlayerController.h"
#include "FirstCharacter.h"
#include "VrCharacter.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "IXRTrackingSystem.h"
#include "IHeadMountedDisplay.h"



ABaseGameMode::ABaseGameMode()
{
	PlayerControllerClass = ABasePlayerController::StaticClass();
	if (IsHeadMountedDisplayEnabled())
	{
		DefaultPawnClass = AVrCharacter::StaticClass();
	}
	else
	{
		DefaultPawnClass = AFirstCharacter::StaticClass();
	}
	bGameOver = false;
}

bool ABaseGameMode::HasMatchEnded() const
{
	return bGameOver;
}

void ABaseGameMode::GameOver()
{
	if (bGameOver == false)
	{
		OnGameOver();
		bGameOver = true;
	}
}

bool ABaseGameMode::IsHeadMountedDisplayEnabled()
{
	return GEngine && GEngine->XRSystem.IsValid() && GEngine->XRSystem->IsHeadTrackingAllowed();
}

bool ABaseGameMode::IsHeadMountedDisplayConnected()
{
	return GEngine && GEngine->XRSystem.IsValid() && GEngine->XRSystem->GetHMDDevice() && GEngine->XRSystem->GetHMDDevice()->IsHMDConnected();
}
