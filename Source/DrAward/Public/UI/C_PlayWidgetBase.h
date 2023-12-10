// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_PlayWidgetBase.generated.h"

/**
 * ゲームプレイ中UI基底クラス
 */
UCLASS()
class DRAWARD_API UC_PlayWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

private:
#pragma region DelegateBindFunction
	UFUNCTION() FText UpdateLifeText();
	UFUNCTION() FText UpdateItemText();
	UFUNCTION() FText UpdateMinuteText();
	UFUNCTION() FText UpdateSecondText();
	UFUNCTION() FText UpdateStageText();
#pragma endregion

protected:
#pragma region BindVariable
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> Life_Text;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> ItemNum_Text;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> Minute_Text;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> Second_Text;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> StageNum_Text;
#pragma endregion

	TObjectPtr<class UC_AwardGameInstanceBase> _agi;
};
