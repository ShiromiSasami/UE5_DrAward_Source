// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/C_AwardGameInstanceBase.h"

#include "Other/C_DrAwardSaveGameBase.h"

#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>


UC_AwardGameInstanceBase::UC_AwardGameInstanceBase()
	:bIsClear(false),
	_life(0),
	_itemNum(0),
	_timeMinute(0),
	_timeSecond(0),
	_stageName(""),
	bIsSaveDataAvailable(false),
	_loadingWaitTime(0.f),
	_saveData(nullptr),
	_saveSlotName("AwardSlot")
{
	
}

void UC_AwardGameInstanceBase::Init()
{
	_loadingWaitTime = 4.f;

	bIsSaveDataAvailable = true;
	auto saveObj = UGameplayStatics::LoadGameFromSlot(_saveSlotName, 0);
	if (!saveObj)
	{
		saveObj = UGameplayStatics::CreateSaveGameObject(UC_DrAwardSaveGameBase::StaticClass());
		bIsSaveDataAvailable = false;
	}
	
	_saveData = Cast<UC_DrAwardSaveGameBase>(saveObj);
}

void UC_AwardGameInstanceBase::Loading(float& loadingTime, UUserWidget** widget) const
{
	const FString WidgetPath = "/Script/UMGEditor.WidgetBlueprint'/Game/BP/UI/BP_LoadingWidget.BP_LoadingWidget_c'";
	if (const auto WidgetClass = TSoftClassPtr<UUserWidget>(FSoftClassPath(*WidgetPath)).LoadSynchronous())
	{
		if (widget)
		{
			*widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
			(*widget)->AddToViewport();
		}
		else
		{
			CreateWidget<UUserWidget>(GetWorld(), WidgetClass)->AddToViewport();
		}
	}

	loadingTime = _loadingWaitTime;
}
