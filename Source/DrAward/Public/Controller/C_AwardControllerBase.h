// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"

#include "C_AwardControllerBase.generated.h"


/**
 * �A���[�h�̃R���g���[���[���N���X
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
	/// ���͐ݒ�̏�����
	/// </summary>
	void SetupInput();

	/// <summary>
	/// �ړ����̓C�x���g
	/// </summary>
	/// <param name="value">���͒l</param>
	void MoveAction(const FInputActionValue& value);
	
private:
	//���͗p�����o
	UPROPERTY(EditAnywhere)
		TObjectPtr<class UInputMappingContext> _imc = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<class UInputAction> _inputMove = nullptr;
};
