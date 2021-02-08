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
	UPaintSaveGame* Painting = UPaintSaveGame::Create();
	Painting->SetState("hello world");
	Painting->SerializeFromWorld(GetWorld());
	UE_LOG(LogTemp, Warning, TEXT("Painting State  %s"), *Painting->GetState());
	Painting->Save();
}

void AVRPawn::Load()
{
	UPaintSaveGame* Painting = UPaintSaveGame::Load();
	if(Painting)
	{
		Painting->DeserializeToWorld(GetWorld());
		UE_LOG(LogTemp, Warning, TEXT("Loading %s"), *Painting->GetState());
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Save game not Found"));
	}
}


