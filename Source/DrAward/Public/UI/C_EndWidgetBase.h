// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_EndWidgetBase.generated.h"

/**
 * エンドUIの基礎クラス
 */
UCLASS()
class DRAWARD_API UC_EndWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

private:

#pragma region DelegateBindFunction
	UFUNCTION() void ClickedRestart();
	UFUNCTION() void ClickedBackTitle();
	UFUNCTION() FText UpdateMinuteText();
	UFUNCTION() FText UpdateSecondText();
	UFUNCTION() FText UpdateStageText();
#pragma endregion

protected:

#pragma region BindVariable
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UButton> Restart_Btn;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UButton> BackTitle_Btn;
	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	TObjectPtr<class UWidgetAnimation> EndWidgetAnimation;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> LastMinute_Text;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> LastSecond_Text;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> LastStageNum_Text;
#pragma endregion

	TObjectPtr<class UC_AwardGameInstanceBase> _agi;
};
