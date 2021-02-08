// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintSaveGame.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Stroke.h"

UPaintSaveGame* UPaintSaveGame::Create()
{
	USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(StaticClass());
	return Cast<UPaintSaveGame>(NewSaveGame);
}

bool UPaintSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, TEXT("Slot1"), 0);
}

UPaintSaveGame* UPaintSaveGame::Load()
{
	return Cast<UPaintSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));
}

void UPaintSaveGame::SerializeFromWorld(UWorld* World)
{
	Strokes.Empty();
	for(TActorIterator<AStroke> StrokeIterator(World); StrokeIterator; ++StrokeIterator)
	{
		Strokes.Add(StrokeIterator->SerializeToStruct());
	}
}

void UPaintSaveGame::DeserializeToWorld(UWorld* World)
{
	ClearWorld(World);
	for (FStrokeState StrokeState : Strokes)
	{
		AStroke::SpawnAndDeserializeFromStruct(World, StrokeState);
	}	
}

void UPaintSaveGame::ClearWorld(UWorld* World)
{
	for(TActorIterator<AStroke> StrokeIterator(World); StrokeIterator; ++StrokeIterator)
	{
		StrokeIterator->Destroy();
		
	}
	
}
	
