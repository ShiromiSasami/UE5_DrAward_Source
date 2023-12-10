// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LS_StartMap.generated.h"

/**
 * スタートレベル用レベルスクリプト
 */
UCLASS()
class DRAWARD_API ALS_StartMap : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ALS_StartMap();

protected:
	virtual void BeginPlay() override;
	
};
