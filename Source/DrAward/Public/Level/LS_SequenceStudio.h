// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LS_SequenceStudio.generated.h"

/**
 * �V�[�P���X�X�^�W�I���x���p���x���X�N���v�g
 */
UCLASS()
class DRAWARD_API ALS_SequenceStudio : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	ALS_SequenceStudio();

protected:
	virtual void BeginPlay() override;
};
