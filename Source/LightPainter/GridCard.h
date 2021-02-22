// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "GridCard.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UGridCard : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UTextBlock* SlotName;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* CardButton;

public:
	void SetPaintingName(FString Name);

private:
	UFUNCTION()
	void CardButtonClicked();

	UPROPERTY()
	FString StringName;
};
