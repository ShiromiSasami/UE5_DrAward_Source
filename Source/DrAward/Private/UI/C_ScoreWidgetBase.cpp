// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_ScoreWidgetBase.h"

#include "GameInstance/C_AwardGameInstanceBase.h"
#include "Other/C_DrAwardSaveGameBase.h"

#include <Components/TextBlock.h>

void UC_ScoreWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

}

bool UC_ScoreWidgetBase::Initialize()
{
	if (!Super::Initialize()) return false;

	if (ScoreStage_Text)
	{
		ScoreStage_Text->TextDelegate.BindUFunction(this, "UpdateScoreStageText");
	}

	if (ScoreTime_Text)
	{
		ScoreTime_Text->TextDelegate.BindUFunction(this, "UpdateScoreTimeText");
	}

	return true;
}

FText UC_ScoreWidgetBase::UpdateScoreStageText()
{
	const auto agi = Cast<UC_AwardGameInstanceBase>(GetGameInstance());
	if (!agi || !agi->IsSaveDataAvailable) return FText();

#define LOCTEXT_NAMESPACE "Score"
	FFormatNamedArguments Args;
	Args.Add(TEXT("Num"), FText::FromString(FString::FromInt(_score.StageNum)));
	FText outputText = FText::Format(LOCTEXT("ScoreStageNum","D{Num}F"), Args);
#undef LOCTEXT_NAMESPACE

	return outputText;
}

FText UC_ScoreWidgetBase::UpdateScoreTimeText()
{
	const auto agi = Cast<UC_AwardGameInstanceBase>(GetGameInstance());
	if (!agi || !agi->IsSaveDataAvailable) return FText();

	auto minute = _score.MinuteNum;
	FString minuteText = FString::FromInt(minute);
	if (minute < 10)
	{
		minuteText = UAwardBlueprintFunctionLibrary::CastIntToFString(minute, 2);
	}

	auto second = _score.SecondNum;
	FString secondText = FString::FromInt(second);
	if (second < 10)
	{
		secondText = UAwardBlueprintFunctionLibrary::CastIntToFString(second, 2);
	}
#define LOCTEXT_NAMESPACE "Score"
	FFormatNamedArguments Args;
	Args.Add(TEXT("Min"), FText::FromString(minuteText));
	Args.Add(TEXT("Sec"), FText::FromString(secondText));
	FText outputText = FText::Format(LOCTEXT("ScoreTime", "{Min}:{Sec}"), Args);
#undef LOCTEXT_NAMESPACE

	return outputText;
}
