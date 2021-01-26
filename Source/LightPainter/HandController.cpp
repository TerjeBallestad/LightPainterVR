// Fill out your copyright notice in the Description page of Project Settings.


#include "HandController.h"
#include "MotionControllerComponent.h"

AHandController::AHandController()
{
	PrimaryActorTick.bCanEverTick = true;

	MotionControllerComponent = CreateDefaultSubobject<UMotionControllerComponent> (TEXT("MotionController"));
	SetRootComponent(MotionControllerComponent);
	MotionControllerComponent->SetShowDeviceModel(true);
}

void AHandController::BeginPlay()
{
	Super::BeginPlay();
}

void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

