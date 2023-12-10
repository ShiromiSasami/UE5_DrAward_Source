// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_StartWidgetBase.generated.h"

/**
 * ゲームスタートUI(タイトル)基礎クラス
 */
UCLASS()
class DRAWARD_API UC_StartWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
#pragma region DelegateBindFunction

	UFUNCTION() void ClickedStart();
	UFUNCTION() void ClickedQuit();
	UFUNCTION() void ClickedBestScore();

#pragma endregion

protected:
#pragma region BindVariable
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UButton> Start_Btn;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UButton> Quit_Btn;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UButton> BestScore_Btn;
#pragma endregion
};
