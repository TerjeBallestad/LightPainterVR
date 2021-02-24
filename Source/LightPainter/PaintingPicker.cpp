// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingPicker.h"


#include "ActionBar.h"
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


	UActionBar* ActionBarWidget = Cast<UActionBar>( ActionBar->GetUserWidgetObject());
	if(ActionBarWidget)
	{
		ActionBarWidget->SetParenPicker(this);
	}
	
	RefreshSlots();
}

void APaintingPicker::AddPainting()
{
	UPaintSaveGame::Create();
	RefreshSlots();
}

void APaintingPicker::RefreshSlots()
{
	UPaintingGrid* PaintingWidget = Cast<UPaintingGrid>( PaintingGrid->GetUserWidgetObject());
	if(!PaintingWidget) return;

	PaintingWidget->ClearPaintings();
	
	int32 i = 0;
	
	for (FString SlotName : UPaintingSaveGameIndex::Load()->GetSlotNames())
	{
		PaintingWidget->AddPainting(i, SlotName);
		++i;
	}
	
}


