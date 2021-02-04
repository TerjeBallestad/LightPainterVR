// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintSaveGame.h"
#include "Kismet/GameplayStatics.h"

UPaintSaveGame* UPaintSaveGame::Create()
{
	USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(StaticClass());
	return Cast<UPaintSaveGame>(NewSaveGame);
}

bool UPaintSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, TEXT("Test"), 0);
}
	
