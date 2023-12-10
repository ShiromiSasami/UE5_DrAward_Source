// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Other/AwardBlueprintFunctionLibrary.h"
#include "Other/AwardScoreStruct.h"
#include "C_ScoreWidgetBase.generated.h"

/**
 * スコアUI基礎クラス
 */
UCLASS()
class DRAWARD_API UC_ScoreWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

private:
#pragma region DelegateBindFunction

	UFUNCTION() FText UpdateScoreStageText();
	UFUNCTION() FText UpdateScoreTimeText();

#pragma endregion

public:
	Property<FAwardScoreStruct> Score
	{
		_score,
		[this](FAwardScoreStruct value) { _score = value; },
		[this]() { return _score; }
	};

protected:
#pragma region BindVariable
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> ScoreStage_Text;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> ScoreTime_Text;
#pragma endregion

	FAwardScoreStruct _score;
};
