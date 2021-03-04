// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"


#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"

void UPaintingGrid::AddPaginationDot(bool Active)
{
	if(!PaginationBox) return;
	UPaginationDot* NewDot = CreateWidget<UPaginationDot>(GetWorld(),DotClass);
	if(!NewDot) return;
	UHorizontalBoxSlot* BoxSlot = PaginationBox->AddChildToHorizontalBox(NewDot);
	BoxSlot->SetPadding(FMargin(DotPadding,0));
	NewDot->SetActive(Active);
}

int32 UPaintingGrid::GetNumberOfSlots() const
{
	return PaintingGrid->GetChildrenCount();
}


void UPaintingGrid::AddPainting(int32 PaintingIndex, FString SlotName)
{
	if(!PaintingGrid) return;
	
	UGridCard* NewWidget = CreateWidget<UGridCard>(GetWorld(), GridCardClass);
	if(!NewWidget) return;
	
	if(USizeBox* SizeBox = Cast<USizeBox>(PaintingGrid->GetChildAt(PaintingIndex)))
	{
		SizeBox->AddChild(NewWidget);
		NewWidget->SetPaintingName(SlotName);
		
	}
}

void UPaintingGrid::ClearPaintings()
{
	for (UWidget* Child : PaintingGrid->GetAllChildren())
	{
		if(USizeBox* SizeBox = Cast<USizeBox>(Child))
		{
			SizeBox->ClearChildren();
		}
	}
}

void UPaintingGrid::ClearDots()
{
	PaginationBox->ClearChildren();
}
