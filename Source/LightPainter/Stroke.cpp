// Fill out your copyright notice in the Description page of Project Settings.


#include "Stroke.h"

#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Math/Rotator.h"

// Sets default values
AStroke::AStroke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StrokeMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("StrokeMeshes"));
	StrokeMeshes->SetupAttachment(Root);
	JointMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("JointMeshes"));
	JointMeshes->SetupAttachment(Root);
}

void AStroke::Update(FVector CursorLocation)
{
	Points.Add(CursorLocation);
	
	if(PreviousCursorLocation.IsNearlyZero())
	{
		PreviousCursorLocation = CursorLocation;
		JointMeshes->AddInstance(GetNextJointTransform(CursorLocation));
	}
	
	StrokeMeshes->AddInstance(GetNextSegmentTransform(CursorLocation));
	JointMeshes->AddInstance(GetNextJointTransform(CursorLocation));

	PreviousCursorLocation = CursorLocation;
}

FStrokeState AStroke::SerializeToStruct() const
{
	FStrokeState StrokeState;
	StrokeState.StrokeClass = GetClass();
	StrokeState.ControlPoints = Points;
	return StrokeState;
}

AStroke* AStroke::SpawnAndDeserializeFromStruct(UWorld* World, const FStrokeState& StrokeState)
{
	AStroke* Stroke = World->SpawnActor<AStroke>(StrokeState.StrokeClass);
	
	for (FVector Point : StrokeState.ControlPoints)
	{
		Stroke->Update(Point);	
	}
	return Stroke;
}

FTransform AStroke::GetNextSegmentTransform(const FVector CurrentLocation) const
{
	FTransform SegmentTransform;

	SegmentTransform.SetLocation(GetNextSegmentLocation(CurrentLocation));
	SegmentTransform.SetRotation(GetNextSegmentRotation(CurrentLocation));
	SegmentTransform.SetScale3D(GetNextSegmentScale(CurrentLocation));
	
	return SegmentTransform;
}

FTransform AStroke::GetNextJointTransform(const FVector CurrentLocation) const
{
	FTransform JointTransform;
	JointTransform.SetLocation(GetTransform().InverseTransformPosition(CurrentLocation));
	return JointTransform;
}

FVector AStroke::GetNextSegmentLocation(FVector CurrentLocation) const
{

	return GetTransform().InverseTransformPosition(PreviousCursorLocation);
}

FQuat AStroke::GetNextSegmentRotation(const FVector CurrentLocation) const
{
	const FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(PreviousCursorLocation, CurrentLocation);
	return Rotator.Quaternion();
}

FVector AStroke::GetNextSegmentScale(const FVector CurrentLocation) const
{
	return FVector((CurrentLocation - PreviousCursorLocation).Size(), 1, 1);
}

