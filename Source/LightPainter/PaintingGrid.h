// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GridCard.h"
#include "PaginationDot.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"

#include "Components/UniformGridPanel.h"

#include "PaintingGrid.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()


protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UUniformGridPanel* PaintingGrid;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* PaginationBox;

public:
	void AddPaginationDot(bool Active);
	int32 GetNumberOfSlots() const;
	void ClearDots();
	
	UFUNCTION(BlueprintCallable)
	void AddPainting(int32 PaintingIndex, FString SlotName);

	UFUNCTION()
	void ClearPaintings();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGridCard> GridCardClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaginationDot> DotClass;

	UPROPERTY(EditDefaultsOnly)
	float DotPadding = 8;
};
