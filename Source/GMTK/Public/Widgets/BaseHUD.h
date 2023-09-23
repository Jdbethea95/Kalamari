// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class GMTK_API UBaseHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void ModifyTimer(int mins, int secs);

protected:
	//reminder in GMTK.Build.cs Added "UMG" and uncommented line 16 for Slates
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* minutes;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* seconds;
	
};
