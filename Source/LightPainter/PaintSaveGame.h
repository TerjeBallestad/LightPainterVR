// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SaveGame.h"
#include "PaintSaveGame.generated.h"

USTRUCT()
struct FStrokeState
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<class AStroke> StrokeClass;

	UPROPERTY()
	TArray<FVector> ControlPoints;
};

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

	void SerializeFromWorld(UWorld* World);
	void DeserializeToWorld(UWorld* World);

private:
	void ClearWorld(UWorld* World);
	// State
	UPROPERTY()
	FString State;
	
	UPROPERTY()
	TArray<FStrokeState> Strokes;
};
