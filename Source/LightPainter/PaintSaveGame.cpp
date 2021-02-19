// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintSaveGame.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Guid.h"
#include "Stroke.h"

UPaintSaveGame* UPaintSaveGame::Create()
{
	UPaintSaveGame* NewSaveGame = Cast<UPaintSaveGame> (UGameplayStatics::CreateSaveGameObject(StaticClass()));
	NewSaveGame->SlotName = FGuid::NewGuid().ToString();
	
	return NewSaveGame;
}

bool UPaintSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

UPaintSaveGame* UPaintSaveGame::Load(FString SlotName)
{
	return Cast<UPaintSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
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
	
