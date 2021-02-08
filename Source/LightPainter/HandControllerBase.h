// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "HandControllerBase.generated.h"

UCLASS()
class LIGHTPAINTER_API AHandControllerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AHandControllerBase();

	virtual void SetHand(const EControllerHand Hand) const { MotionControllerComponent->SetTrackingSource(Hand); };
	virtual void TriggerPressed() {};
	virtual void TriggerReleased() {};

private:
	UPROPERTY(VisibleAnywhere)
	UMotionControllerComponent* MotionControllerComponent;

};
