// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingSaveGameIndex.h"

#include "Kismet/GameplayStatics.h"

const FString UPaintingSaveGameIndex::SLOT_NAME = "PaintingIndex";

UPaintingSaveGameIndex* UPaintingSaveGameIndex::Load()
{
	UPaintingSaveGameIndex* Index = Cast<UPaintingSaveGameIndex>(UGameplayStatics::LoadGameFromSlot(SLOT_NAME, 0));

	if(!Index)
	{
		Index = Cast<UPaintingSaveGameIndex> (UGameplayStatics::CreateSaveGameObject(StaticClass()));
		Index->Save();
	}
	return Index;
}

bool UPaintingSaveGameIndex::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SLOT_NAME, 0);
}

void UPaintingSaveGameIndex::AddSaveGame(UPaintSaveGame* SaveGame)
{
	SlotNames.Add(SaveGame->GetSlotName());
}

TArray<FString> UPaintingSaveGameIndex::GetSlotNames() const
{
	return SlotNames;
}
