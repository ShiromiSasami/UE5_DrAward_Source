// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_EndWidgetBase.h"

#include "Other/AwardBlueprintFunctionLibrary.h"
#include "GameInstance/C_AwardGameInstanceBase.h"

#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include <Components/TextBlock.h>

void UC_EndWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();
}

bool UC_EndWidgetBase::Initialize()
{
	if (!Super::Initialize()) return false;

	_agi = Cast<UC_AwardGameInstanceBase>(GetGameInstance());

    if (Restart_Btn)
    {
        Restart_Btn->OnClicked.AddDynamic(this, &UC_EndWidgetBase::ClickedRestart);
    }

    if (BackTitle_Btn)
    {
        BackTitle_Btn->OnClicked.AddDynamic(this, &UC_EndWidgetBase::ClickedBackTitle);
    }

    if (EndWidgetAnimation)
    {
        PlayAnimation(EndWidgetAnimation);
    }

    
	if (LastMinute_Text)
	{
		LastMinute_Text->TextDelegate.BindUFunction(this, "UpdateMinuteText");
	}
	if (LastSecond_Text)
	{
		LastSecond_Text->TextDelegate.BindUFunction(this, "UpdateSecondText");
	}
	if (LastStageNum_Text)
	{
		LastStageNum_Text->TextDelegate.BindUFunction(this, "UpdateStageText");
	}

	return true;
}

void UC_EndWidgetBase::ClickedRestart()
{
	auto agi = Cast<UC_AwardGameInstanceBase>(UGameplayStatics::GetGameInstance(GetWorld()));
	float loadTime;
	agi->Loading(loadTime);

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, [this] {UGameplayStatics::OpenLevel(GetWorld(), "Main"); }, loadTime, false);
}

void UC_EndWidgetBase::ClickedBackTitle()
{
	auto agi = Cast<UC_AwardGameInstanceBase>(UGameplayStatics::GetGameInstance(GetWorld()));
	float loadTime;
	agi->Loading(loadTime);

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, [this] {UGameplayStatics::OpenLevel(GetWorld(), "Start"); }, loadTime, false);
}

FText UC_EndWidgetBase::UpdateMinuteText()
{
	if (!_agi) return FText::FromString("00");

	int8 minute = _agi->Minute;
	FText outputText = FText::FromString(FString::FromInt(minute));
	if (minute < 10)
	{
		FString text = UAwardBlueprintFunctionLibrary::CastIntToFString(minute, 2);
		outputText = FText::FromString(text);
	}

	return outputText;
}

FText UC_EndWidgetBase::UpdateSecondText()
{
	if (!_agi) return FText::FromString("00");

	int8 second = _agi->Second;
	FText outputText = FText::FromString(FString::FromInt(second));
	if (second < 10)
	{
		FString text = UAwardBlueprintFunctionLibrary::CastIntToFString(second, 2);
		outputText = FText::FromString(text);
	}

	return outputText;
}

FText UC_EndWidgetBase::UpdateStageText()
{
	if (!_agi) return FText::FromString("0");
	FString stageName = _agi->StageName;
	int8 startIndex = 5;
	FString numText = stageName.Mid(startIndex, stageName.Len() - startIndex);

	return FText::FromString(numText);
}
