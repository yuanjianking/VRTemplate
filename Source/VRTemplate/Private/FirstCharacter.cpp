// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AFirstCharacter::AFirstCharacter() : Super()
{
	// Create a CameraComponent	
	VrCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("VrCameraComponent"));
	VrCameraComponent->SetupAttachment(GetCapsuleComponent());
	VrCameraComponent->SetRelativeLocation(FVector(-70.f, 0.f, 95.f)); 
	VrCameraComponent->SetRelativeRotation(FRotator(-20, 0, 0));
	VrCameraComponent->bUsePawnControlRotation = true;


	USkeletalMeshComponent* MeshComponent = GetMesh();
	USkeletalMesh* NewMesh  = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/Blueprint/yue/Standing_Idle.Standing_Idle"));
	if(NewMesh != nullptr)
	{
		MeshComponent->SetSkeletalMeshAsset(NewMesh);
		MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	}
	//static ConstructorHelpers::FClassFinder<UAnimBlueprintGeneratedClass> NewClass(TEXT("/Game/Blueprint/Character/FirstAnim.FirstAnim_C"));
	UAnimBlueprintGeneratedClass* NewClass = LoadObject<UAnimBlueprintGeneratedClass>(nullptr, TEXT("/Game/Blueprint/Character/FirstAnim.FirstAnim_C"));
	if(NewClass != nullptr)
	{
		MeshComponent->SetAnimInstanceClass(NewClass);
	}

}

void AFirstCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AFirstCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFirstCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
