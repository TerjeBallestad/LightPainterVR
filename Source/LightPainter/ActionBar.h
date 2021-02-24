// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PaintingPicker.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "ActionBar.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UActionBar : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	void SetParenPicker(APaintingPicker* Picker) { ParentPicker = Picker; }
	
protected:
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* AddButton;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* DeleteButton;

private:
	UFUNCTION()
	void AddButtonClicked();

	UFUNCTION()
	void DeleteButtonClicked();

	UPROPERTY()
	APaintingPicker* ParentPicker;
	
};
