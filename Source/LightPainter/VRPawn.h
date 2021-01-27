// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HandController.h"
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
	void RightTriggerPressed(){ if(RightMController) RightMController->TriggerPressed(); };
	void RightTriggerReleased(){ if(RightMController) RightMController->TriggerReleased(); };
	
	// Config
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandController> HandControllerClass;

	// Components
	UPROPERTY(VisibleAnywhere)
	USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* VRCamera;
	
	// Reference
	UPROPERTY(VisibleAnywhere)
	AHandController* RightMController;
};