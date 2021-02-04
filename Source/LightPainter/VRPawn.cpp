// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"

#include "Camera/CameraComponent.h"
#include "PaintSaveGame.h"

// Sets default values
AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(VRRoot);
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("RightTrigger",IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction("RightTrigger",IE_Released, this, &AVRPawn::RightTriggerReleased);
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

	UPaintSaveGame* Painting = UPaintSaveGame::Create();
	Painting->Save();
	
}

