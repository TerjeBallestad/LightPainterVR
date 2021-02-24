// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"


#include "HandControllerBase.h"
#include "PaintingGameMode.h"
#include "PaintingSaveGameIndex.h"
#include "Camera/CameraComponent.h"
#include "PaintSaveGame.h"
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
	
	RightMController = GetWorld()->SpawnActor<AHandControllerBase>(PaintBrushHandControllerClass);
	if(RightMController != nullptr)
	{
		RightMController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightMController->SetOwner(this);
		RightMController->SetHand(EControllerHand::Right);
	}
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"),IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"),IE_Released, this, &AVRPawn::RightTriggerReleased);
	PlayerInputComponent->BindAction(TEXT("Save"), IE_Released, this, &AVRPawn::Save);
}

void AVRPawn::Save()
{
	auto GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());
	if(!GameMode) return;
	GameMode->Save();

	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}


