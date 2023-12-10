// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LS_SequenceStudio.generated.h"

/**
 * シーケンススタジオレベル用レベルスクリプト
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
