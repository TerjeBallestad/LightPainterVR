// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"



#include "EngineUtils.h"
#include "HandControllerBase.h"
#include "PaintingPicker.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

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

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	if(!RightHandControllerClass) return;
	RightMController = GetWorld()->SpawnActor<AHandControllerBase>(RightHandControllerClass);
	RightMController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	RightMController->SetOwner(this);
	RightMController->SetHand(EControllerHand::Right);
	
	if(!LeftHandControllerClass) return;
	LeftMController = GetWorld()->SpawnActor<AHandControllerBase>(LeftHandControllerClass);
	LeftMController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	LeftMController->SetOwner(this);
	LeftMController->SetHand(EControllerHand::Left);
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"),IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"),IE_Released, this, &AVRPawn::RightTriggerReleased);

	PlayerInputComponent->BindAxis(TEXT("PaginateRight"), this, &AVRPawn::PaginateRightAxisInput);
}

void AVRPawn::PaginateRightAxisInput(float Value)
{
	int32 PaginationInput = 0;
	PaginationInput += Value > PaginationInputThreshold ? 1 : 0;
	PaginationInput += Value < -PaginationInputThreshold ? -1 : 0;

	if(PaginationInput != PreviousPaginationInput && PaginationInput != 0)
	{
		UpdateCurrentPage(PaginationInput);
	}
	PreviousPaginationInput = PaginationInput;
}

void AVRPawn::UpdateCurrentPage(int32 Offset)
{
	for(TActorIterator<APaintingPicker> PaintingPickerItr(GetWorld()); PaintingPickerItr; ++PaintingPickerItr)
	{
		PaintingPickerItr->UpdateCurrentPage(Offset);
	}
}


