// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"

#include "Components/SizeBox.h"

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
