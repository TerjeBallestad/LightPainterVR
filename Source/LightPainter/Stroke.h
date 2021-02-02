// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/InstancedStaticMeshComponent.h"
 #include "GameFramework/Actor.h"
#include "Stroke.generated.h"

UCLASS()
class LIGHTPAINTER_API AStroke : public AActor
{
	GENERATED_BODY()
	
public:	
	AStroke();

	void Update(FVector CursorLocation);

private:

	FTransform GetNextSegmentTransform(FVector CurrentLocation);
	FVector GetNextSegmentLocation(FVector CurrentLocation);
	FQuat GetNextSegmentRotation(FVector CurrentLocation);
	FVector GetNextSegmentScale (FVector CurrentLocation);

	// Components
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* StrokeMeshes;

	// State
	FVector PreviousCursorLocation;
};
