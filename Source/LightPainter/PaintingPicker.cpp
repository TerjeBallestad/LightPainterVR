// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingPicker.h"

#include "PaintingGrid.h"
#include "PaintingSaveGameIndex.h"

APaintingPicker::APaintingPicker()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	PaintingGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaintingGrid"));
	PaintingGrid->SetupAttachment(Root);
	
	ActionBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionBar"));
	ActionBar->SetupAttachment(Root);
}

void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();

	UPaintingSaveGameIndex* Index = UPaintingSaveGameIndex::Load();
	UPaintingGrid* PaintingWidget = Cast<UPaintingGrid>( PaintingGrid->GetUserWidgetObject());
	if(!PaintingWidget) return;
	int32 PaintingIndex = 0;
	
	for (FString SlotName : Index->GetSlotNames())
	{
		PaintingWidget->AddPainting(PaintingIndex, SlotName);
		++PaintingIndex;
	}
}



