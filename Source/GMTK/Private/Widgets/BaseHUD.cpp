// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BaseHUD.h"

void UBaseHUD::ModifyTimer(int mins, int secs)
{
	FFormatNamedArguments Args;
	Args.Add(TEXT("Minutes"), mins);
	Args.Add(TEXT("Seconds"), secs);
	if (mins < 10)
		minutes->SetText(FText::Format(INVTEXT("0{Minutes}"), Args));
	else
		minutes->SetText(FText::Format(INVTEXT("{Minutes}"), Args));

	if (secs < 10)
		seconds->SetText(FText::Format(INVTEXT("0{Seconds}"), Args));
	else
		seconds->SetText(FText::Format(INVTEXT("{Seconds}"), Args));
}
