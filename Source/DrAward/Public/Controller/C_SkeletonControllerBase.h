// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_SkeletonControllerBase.generated.h"

/**
 * �X�P���g���̃R���g���[���[���N���X
 */
UCLASS()
class DRAWARD_API AC_SkeletonControllerBase : public AAIController
{
	GENERATED_BODY()
public :
	AC_SkeletonControllerBase();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	/// <summary>
	/// GameMode�����x���ǂݍ��݂��������C�x���g
	/// </summary>
	UFUNCTION()
	void LoadStreamLevelCompleted();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class AC_SkeletonBase> _character = nullptr;
};
