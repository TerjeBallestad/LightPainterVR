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

void APaintingPicker::UpdateCurrentPage(int32 Offset)
{
	CurrentPage = FMath::Clamp(CurrentPage + Offset, 0, GetNumberOfPages()-1);
	Refresh();
}

void APaintingPicker::RefreshSlots()
{
	if(!GetPaintingGrid()) return;

	GetPaintingGrid()->ClearPaintings();
	
	int32 StartOffset = CurrentPage * GetPaintingGrid()->GetNumberOfSlots();
	TArray<FString> Slots = UPaintingSaveGameIndex::Load()->GetSlotNames();

	for (int32 i = 0; i < GetPaintingGrid()->GetNumberOfSlots() && Slots.Num() > i + StartOffset; ++i)
	{
		GetPaintingGrid()->AddPainting(i, Slots[i + StartOffset]);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Number of Pages %d"), CurrentPage * GetPaintingGrid()->GetNumberOfSlots())
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


