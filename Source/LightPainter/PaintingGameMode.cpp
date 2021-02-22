// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGameMode.h"

#include "Kismet/GameplayStatics.h"

void APaintingGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	PaintingName = UGameplayStatics::ParseOption(Options, "SlotName");

	UE_LOG(LogTemp, Warning, TEXT("Slot Name: %s"), *PaintingName);
}
