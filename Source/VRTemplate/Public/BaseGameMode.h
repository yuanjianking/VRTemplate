// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VRTemplate.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VRTEMPLATE_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ABaseGameMode();

	/** Returns true if GameOver() has been called, false otherwise */
	virtual bool HasMatchEnded() const override;

	/** Called when the game is over i.e. the player dies, the time runs out or the
	 *	game is finished*/
	UFUNCTION(BlueprintCallable, Category = Game)
	virtual void GameOver();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Game, meta = (DisplayName = "OnGameOver", ScriptName = "OnGameOver"))
	void OnGameOver();

	UPROPERTY(BlueprintReadOnly, Category = Game)
	uint32 bGameOver : 1;

private:
	bool IsHeadMountedDisplayEnabled();

	bool IsHeadMountedDisplayConnected();
};
