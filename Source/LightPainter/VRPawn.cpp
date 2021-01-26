// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"

#include "Camera/CameraComponent.h"
#include "HandController.h"

// Sets default values
AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(VRRoot);
}

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	RightMController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
	if(RightMController != nullptr)
	{
		RightMController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightMController->SetOwner(this);
		RightMController->SetHand(EControllerHand::Right);
	}
}

