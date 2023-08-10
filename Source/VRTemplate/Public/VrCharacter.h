// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "VrCharacter.generated.h"

/**
 * 
 */
UCLASS()
class VRTEMPLATE_API AVrCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AVrCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* VrCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* MotionControllerLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* MotionControllerRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* MotionControllerLeftAim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* MotionControllerRightAim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	class UWidgetInteractionComponent* WidgetInteractionLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	class UWidgetInteractionComponent* WidgetInteractionRight;

protected:
	void LeftPointPress(const FInputActionValue& Value);

	void RightPointPress(const FInputActionValue& Value);

	void LeftPointRelease(const FInputActionValue& Value);

	void RightPointRelease(const FInputActionValue& Value);
};
