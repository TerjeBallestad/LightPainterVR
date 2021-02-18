// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingPicker.h"

#include "PaintingGrid.h"

APaintingPicker::APaintingPicker()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	PaintingGrid1 = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaintingGrid"));
	PaintingGrid1->SetupAttachment(Root);
	
	ActionBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionBar"));
	ActionBar->SetupAttachment(Root);
}

void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();

	if(UPaintingGrid* PaintingWidget = Cast<UPaintingGrid>( PaintingGrid1->GetUserWidgetObject()))
	{
		PaintingWidget->AddPainting();
	}
	
}



