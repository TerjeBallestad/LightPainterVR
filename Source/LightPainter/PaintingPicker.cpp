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

	
	if(GetPaintingGrid())
	{
		GetPaintingGrid()->AddPaginationDot(true);	
		GetPaintingGrid()->AddPaginationDot(false);	
		GetPaintingGrid()->AddPaginationDot(false);	
	}

	UActionBar* ActionBarWidget = Cast<UActionBar>( ActionBar->GetUserWidgetObject());
	if(ActionBarWidget)
	{
		ActionBarWidget->SetParenPicker(this);
	}

	Refresh();
}

void APaintingPicker::AddPainting()
{
	UPaintSaveGame::Create();
	Refresh();
}

void APaintingPicker::ToggleDeleteMode()
{
	bDeleteMode = !bDeleteMode;
	if(!GetPaintingGrid()) return;
	GetPaintingGrid()->ClearPaintings();

}

void APaintingPicker::RefreshSlots()
{
	if(!GetPaintingGrid()) return;

	GetPaintingGrid()->ClearPaintings();
	
	int32 i = 0;
	
	for (FString SlotName : UPaintingSaveGameIndex::Load()->GetSlotNames())
	{
		GetPaintingGrid()->AddPainting(i, SlotName);
		++i;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Number of Pages %d"), GetNumberOfPages())
}

void APaintingPicker::RefreshDots()
{
	if(!GetPaintingGrid()) return;
	GetPaintingGrid()->ClearDots();
	for (int i = 0; i < GetNumberOfPages(); ++i)
	{
		GetPaintingGrid()->AddPaginationDot(i == CurrentPage);
	}
	
}

int32 APaintingPicker::GetNumberOfPages()
{
	if(!GetPaintingGrid()) return 0;
	int32 SlotAmount = UPaintingSaveGameIndex::Load()->GetSlotNames().Num();
	return FMath::DivideAndRoundUp(SlotAmount, GetPaintingGrid()->GetNumberOfSlots());
}


