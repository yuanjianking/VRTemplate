// Fill out your copyright notice in the Description page of Project Settings.


#include "VrCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Components/WidgetInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MotionControllerComponent.h"

AVrCharacter::AVrCharacter() : Super()
{
	// Create a CameraComponent	
	VrCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("VrCameraComponent"));
	VrCameraComponent->SetupAttachment(GetCapsuleComponent());
	VrCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	VrCameraComponent->bUsePawnControlRotation = true;

	// Create MotionController
	MotionControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerLeft"));
	MotionControllerLeft->SetupAttachment(GetCapsuleComponent());
	MotionControllerLeft->SetTrackingMotionSource(TEXT("Left"));

	MotionControllerRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerRight"));
	MotionControllerRight->SetupAttachment(GetCapsuleComponent());
	MotionControllerRight->SetTrackingMotionSource(TEXT("Right"));

	MotionControllerLeftAim = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerLeftAim"));
	MotionControllerLeftAim->SetupAttachment(GetCapsuleComponent());
	MotionControllerLeftAim->SetTrackingMotionSource(TEXT("LeftAim"));

	MotionControllerRightAim = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerRightAim"));
	MotionControllerRightAim->SetupAttachment(GetCapsuleComponent());
	MotionControllerRightAim->SetTrackingMotionSource(TEXT("RightAim"));

	WidgetInteractionLeft = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionLeft"));
	WidgetInteractionLeft->SetupAttachment(MotionControllerLeftAim);
	WidgetInteractionLeft->bShowDebug = true;
	WidgetInteractionLeft->DebugColor = FColor::Blue;
	WidgetInteractionLeft->InteractionDistance = 1000.0f;

	WidgetInteractionRight = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractionRight"));
	WidgetInteractionRight->SetupAttachment(MotionControllerRightAim);
	WidgetInteractionRight->bShowDebug = true;
	WidgetInteractionRight->DebugColor = FColor::Blue;
	WidgetInteractionRight->InteractionDistance = 1000.0f;
}

void AVrCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AVrCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVrCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//LeftPoint
		UInputAction* LeftPointAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Blueprint/Input/Actions/IA_Point_Left.IA_Point_Left"));
		if (LeftPointAction != nullptr)
		{
			EnhancedInputComponent->BindAction(LeftPointAction, ETriggerEvent::Started, this, &AVrCharacter::LeftPointPress);
			EnhancedInputComponent->BindAction(LeftPointAction, ETriggerEvent::Completed, this, &AVrCharacter::LeftPointRelease);
		}
		//RightPoint
		UInputAction* RightPointAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Blueprint/Input/Actions/IA_Point_Right.IA_Point_Right"));
		if (RightPointAction != nullptr)
		{
			EnhancedInputComponent->BindAction(RightPointAction, ETriggerEvent::Started, this, &AVrCharacter::RightPointPress);
			EnhancedInputComponent->BindAction(RightPointAction, ETriggerEvent::Completed, this, &AVrCharacter::RightPointRelease);
		}
	}
}

void AVrCharacter::LeftPointPress(const FInputActionValue& Value)
{
	WidgetInteractionLeft->PressPointerKey(EKeys::LeftMouseButton);
}

void AVrCharacter::RightPointPress(const FInputActionValue& Value)
{
	WidgetInteractionRight->PressPointerKey(EKeys::LeftMouseButton);
}

void AVrCharacter::LeftPointRelease(const FInputActionValue& Value)
{
	WidgetInteractionLeft->ReleasePointerKey(EKeys::LeftMouseButton);
}

void AVrCharacter::RightPointRelease(const FInputActionValue& Value)
{
	WidgetInteractionRight->ReleasePointerKey(EKeys::LeftMouseButton);
}
