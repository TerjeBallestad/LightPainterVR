// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"


#include "HandControllerBase.h"
#include "PaintingSaveGameIndex.h"
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

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	UPaintSaveGame* Painting = UPaintSaveGame::Create();
	if(Painting)
	{
		Painting->Save();
		CurrentSlotName = Painting->GetSlotName();
	}
	
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
	PlayerInputComponent->BindAction(TEXT("Load"), IE_Released, this, &AVRPawn::Load);
}

void AVRPawn::Save()
{
	UPaintSaveGame* Painting = UPaintSaveGame::Load(CurrentSlotName);
	if(Painting)
	{
		Painting->SetState("hello world");
		Painting->SerializeFromWorld(GetWorld());
		UE_LOG(LogTemp, Warning, TEXT("Painting State  %s"), *Painting->GetState());
		Painting->Save();
	}
}

void AVRPawn::Load()
{
	UPaintingSaveGameIndex* Index = UPaintingSaveGameIndex::Load();
	if(Index)
	{
		for (FString SlotName : Index->GetSlotNames())
		{
			UE_LOG(LogTemp, Warning, TEXT("Slot: %s"), *SlotName);	
		}
	}
	UPaintSaveGame* Painting = UPaintSaveGame::Load(CurrentSlotName);
	if(Painting)
	{
		Painting->DeserializeToWorld(GetWorld());
		UE_LOG(LogTemp, Warning, TEXT("Loading %s"), *Painting->GetState());
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Save game not Found"));
	}
}


