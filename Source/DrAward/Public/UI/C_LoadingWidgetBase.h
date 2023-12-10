// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_LoadingWidgetBase.generated.h"

/**
 * ���[�h���UI���N���X
 */
UCLASS()
class DRAWARD_API UC_LoadingWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

protected:

#pragma region BindVariable
	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	TObjectPtr<class UWidgetAnimation> LoadingAnimation;
#pragma endregion
};
