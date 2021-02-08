// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintBrushHandController.h"
#include "MotionControllerComponent.h"

APaintBrushHandController::APaintBrushHandController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APaintBrushHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentStroke)
	{
		CurrentStroke->Update(GetActorLocation());
	}
}

void APaintBrushHandController::TriggerPressed()
{
	Super::TriggerPressed();
	CurrentStroke = GetWorld()->SpawnActor<AStroke>(StrokeClass);
}

void APaintBrushHandController::TriggerReleased()
{
	Super::TriggerReleased();
	CurrentStroke = nullptr;
}

void APaintBrushHandController::BeginPlay()
{
	Super::BeginPlay();
}


