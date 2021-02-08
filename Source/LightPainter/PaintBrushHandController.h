// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HandControllerBase.h"
#include "Stroke.h"
#include "PaintBrushHandController.generated.h"

UCLASS()
class LIGHTPAINTER_API APaintBrushHandController : public AHandControllerBase
{
	GENERATED_BODY()
	
public:	
	APaintBrushHandController();

	virtual void TriggerPressed() override;
	virtual void TriggerReleased() override;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	// Components

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AStroke> StrokeClass;

	// State
	UPROPERTY()
	AStroke* CurrentStroke;

};
