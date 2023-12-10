// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"

#include "C_AwardControllerBase.generated.h"


/**
 * アワードのコントローラー基底クラス
 */
UCLASS()
class DRAWARD_API AC_AwardControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	AC_AwardControllerBase();

protected:
	virtual void BeginPlay() override;

private:
	/// <summary>
	/// 入力設定の初期化
	/// </summary>
	void SetupInput();

	/// <summary>
	/// 移動入力イベント
	/// </summary>
	/// <param name="value">入力値</param>
	void MoveAction(const FInputActionValue& value);
	
private:
	//入力用メンバ
	UPROPERTY(EditAnywhere)
		TObjectPtr<class UInputMappingContext> _imc = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<class UInputAction> _inputMove = nullptr;
};
