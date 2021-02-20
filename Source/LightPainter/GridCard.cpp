// Fill out your copyright notice in the Description page of Project Settings.


#include "GridCard.h"

void UGridCard::SetPaintingName(FString Name)
{
	SlotName->SetText(FText::FromString(Name));
}
