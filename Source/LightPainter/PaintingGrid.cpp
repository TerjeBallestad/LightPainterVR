// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"

#include "EdGraph/EdGraphNode.h"

void UPaintingGrid::AddPainting()
{
	if(PaintingGrid)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grid name: %s"), *PaintingGrid->GetName());
		
	}
}
