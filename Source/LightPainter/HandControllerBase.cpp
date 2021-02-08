// Fill out your copyright notice in the Description page of Project Settings.


#include "HandControllerBase.h"

// Sets default values
AHandControllerBase::AHandControllerBase()
{
	PrimaryActorTick.bCanEverTick = false;

	MotionControllerComponent = CreateDefaultSubobject<UMotionControllerComponent> (TEXT("MotionController"));
	SetRootComponent(MotionControllerComponent);
	MotionControllerComponent->SetShowDeviceModel(true);

}


