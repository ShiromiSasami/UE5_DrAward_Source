// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_AI_Award.generated.h"

/**
 * Awardのアニメーション基礎クラス
 */
UCLASS()
class DRAWARD_API UC_AI_Award : public UAnimInstance
{
	GENERATED_BODY()
public:
	UC_AI_Award();

public: 
	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	//歩行速度 
	UPROPERTY(BlueprintReadOnly)
	float _speed;
	UPROPERTY(BlueprintReadOnly)
	bool _isClear;
	UPROPERTY(BlueprintReadOnly)
	bool _endAnim;

	TObjectPtr<class ACharacter> _character = nullptr;
};
