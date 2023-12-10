// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_LoadingWidgetBase.h"
#include "DrAward/DebugTools.h"

void UC_LoadingWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UC_LoadingWidgetBase::Initialize()
{
	if (!Super::Initialize()) return false;

	if (LoadingAnimation)
	{
		PlayAnimation(LoadingAnimation, 0.f, 0);
	}

	return false;
}
