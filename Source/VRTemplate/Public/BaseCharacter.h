// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VRTemplate.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class VRTEMPLATE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);


};
