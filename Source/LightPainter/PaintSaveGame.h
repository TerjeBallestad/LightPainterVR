// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PaintSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	static UPaintSaveGame* Create();
	bool Save();
	static UPaintSaveGame* Load();

	void SetState(FString NewState) { State = NewState; }
	FString GetState() const { return  State; }

private:
	// State
	UPROPERTY()
	FString State;
};
