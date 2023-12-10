// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_PlayWidgetBase.h"

#include "Other/AwardBlueprintFunctionLibrary.h"
#include "GameInstance/C_AwardGameInstanceBase.h"

#include <Components/TextBlock.h>

void UC_PlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UC_PlayWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	_agi = Cast<UC_AwardGameInstanceBase>(GetGameInstance());

	if (Life_Text)
	{
		Life_Text->TextDelegate.BindUFunction(this, "UpdateLifeText");
	}
	if (ItemNum_Text)
	{
		ItemNum_Text->TextDelegate.BindUFunction(this, "UpdateItemText");
	}
	if (Minute_Text)
	{
		Minute_Text->TextDelegate.BindUFunction(this, "UpdateMinuteText");
	}
	if (Second_Text)
	{
		Second_Text->TextDelegate.BindUFunction(this, "UpdateSecondText");
	}
	if (StageNum_Text)
	{
		StageNum_Text->TextDelegate.BindUFunction(this, "UpdateStageText");
	}

	return true;
}

FText UC_PlayWidget::UpdateItemText()
{
	if (!_agi) return FText::FromString("00");

	auto itemNum = _agi->ItemNum;
	FText outputText = FText::FromString(FString::FromInt(itemNum));
	if (itemNum < 10)
	{
		FString text = UAwardBlueprintFunctionLibrary::CastIntToFString(itemNum, 2);
		outputText = FText::FromString(text);
	}

	return outputText;
}

FText UC_PlayWidget::UpdateLifeText()
{
	if (!_agi) return FText::FromString("00");

	auto lifeNum = _agi->Life;
	FText outputText = FText::FromString(FString::FromInt(lifeNum));
	if (lifeNum < 10)
	{
		FString text = UAwardBlueprintFunctionLibrary::CastIntToFString(lifeNum, 2);
		outputText = FText::FromString(text);
	}

	return outputText;
}

FText UC_PlayWidget::UpdateMinuteText()
{
	if (!_agi) return FText::FromString("00");

	auto minute = _agi->Minute;
	FText outputText = FText::FromString(FString::FromInt(minute));
	if (minute < 10)
	{
		FString text = UAwardBlueprintFunctionLibrary::CastIntToFString(minute, 2);
		outputText = FText::FromString(text);
	}

	return outputText;
}

FText UC_PlayWidget::UpdateSecondText()
{
	if (!_agi) return FText::FromString("00");

	auto second = _agi->Second;
	FText outputText = FText::FromString(FString::FromInt(second));
	if (second < 10)
	{
		FString text = UAwardBlueprintFunctionLibrary::CastIntToFString(second, 2);
		outputText = FText::FromString(text);
	}

	return outputText;
}

FText UC_PlayWidget::UpdateStageText()
{
	if (!_agi) return FText::FromString("0");
	FString stageName = _agi->StageName;
	int8 startIndex = 5;
	FString numText = stageName.Mid(startIndex, stageName.Len() - startIndex);
	
	return FText::FromString(numText);
}
