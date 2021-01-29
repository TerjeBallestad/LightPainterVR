// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "Stroke.h"
#include "GameFramework/Actor.h"
#include "HandController.generated.h"

UCLASS()
class LIGHTPAINTER_API AHandController : public AActor
{
	GENERATED_BODY()
	
public:	
	AHandController();

	void SetHand(const EControllerHand Hand) const { MotionControllerComponent->SetTrackingSource(Hand); };
	void TriggerPressed();
	void TriggerReleased();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	// Components
	UPROPERTY(VisibleAnywhere)
	UMotionControllerComponent* MotionControllerComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStroke> StrokeClass;

	// State
	UPROPERTY()
	AStroke* CurrentStroke;

};
