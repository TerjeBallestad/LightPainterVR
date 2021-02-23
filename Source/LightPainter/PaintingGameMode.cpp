// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGameMode.h"


#include "PaintSaveGame.h"
#include "Kismet/GameplayStatics.h"

void APaintingGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	SlotName = UGameplayStatics::ParseOption(Options, "SlotName");

	UE_LOG(LogTemp, Warning, TEXT("Slot Name: %s"), *SlotName);
}

void APaintingGameMode::BeginPlay()
{
	Super::BeginPlay();

	UPaintSaveGame* Painting = UPaintSaveGame::Load(SlotName);
	if(Painting)
	{
		Painting->DeserializeToWorld(GetWorld());
		UE_LOG(LogTemp, Warning, TEXT("Loading %s"), *Painting->GetState());
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Save game not Found %s"), *SlotName);
	}
}

