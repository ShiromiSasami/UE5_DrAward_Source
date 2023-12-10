// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_ScoreBoardWidgetBase.generated.h"

/**
 * スコアボードUI基礎クラス
 */
UCLASS()
class DRAWARD_API UC_ScoreBoard : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

private:
#pragma region DelegateBindFunction

	UFUNCTION() void ClickedBackTitle();

#pragma endregion

protected:
#pragma region BindVariable
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UButton> BackTitle_Btn;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UVerticalBox> ScoreBox;
#pragma endregion
};
