// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PaintBrushHandController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "VRPawn.generated.h"

UCLASS()
class LIGHTPAINTER_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	AVRPawn();


protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void RightTriggerPressed(){ if(RightMController) RightMController->TriggerPressed(); }
	void RightTriggerReleased(){ if(RightMController) RightMController->TriggerReleased(); }

	void PaginateRightAxisInput(float Value);
	void UpdateCurrentPage(int32 Offset);

	// Config
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> RightHandControllerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> LeftHandControllerClass;

	UPROPERTY()
	float PaginationInputThreshold = 0.9;

	// Components
	UPROPERTY(VisibleAnywhere)
	USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* VRCamera;
	
	// Reference
	UPROPERTY()
	AHandControllerBase* RightMController;

	UPROPERTY()
	AHandControllerBase* LeftMController;

	// State
	int32 PreviousPaginationInput;
};
