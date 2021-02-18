// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"


#include "Components/SizeBox.h"

void UPaintingGrid::AddPainting()
{
	if(!PaintingGrid) return;
	
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), GridCardClass);
	if(!NewWidget) return;
	
	if(USizeBox* SizeBox = Cast<USizeBox>(PaintingGrid->GetChildAt(0)))
	{
		SizeBox->AddChild(NewWidget);
	}
}
