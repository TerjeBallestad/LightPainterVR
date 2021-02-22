// Fill out your copyright notice in the Description page of Project Settings.


#include "GridCard.h"

#include "Kismet/GameplayStatics.h"

void UGridCard::SetPaintingName(FString Name)
{
	StringName = Name;
	SlotName->SetText(FText::FromString(Name));
	

	CardButton->OnClicked.AddDynamic(this, &UGridCard::CardButtonClicked);
}

void UGridCard::CardButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"), true, "SlotName=" + StringName);
}
