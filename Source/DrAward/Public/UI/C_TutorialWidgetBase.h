// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_TutorialWidgetBase.generated.h"

/**
 * チュートリアルUI基礎クラス
 */
UCLASS()
class DRAWARD_API UC_TutorialWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

	//BindFunction
	UFUNCTION()
	void ClickedClose();

protected:

#pragma region BindVariable
	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	TObjectPtr<class UWidgetAnimation> TutorialAnimation;
	UPROPERTY(Transient, meta = (BindWidgetOptional))
	TObjectPtr<class UButton> Close_Btn;
#pragma endregion

};
