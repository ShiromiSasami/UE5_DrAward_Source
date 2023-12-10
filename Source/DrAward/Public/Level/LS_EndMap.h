// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LS_EndMap.generated.h"

/**
 * エンドレベル用のレベルスクリプト
 */
UCLASS()
class DRAWARD_API ALS_EndMap : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ALS_EndMap();
	
protected:
	virtual void BeginPlay() override;

	/// <summary>
	/// /Score用のデータ保存
	/// </summary>
	/// <param name="agi">ゲームインスタンス</param>
	void Save(class UC_AwardGameInstanceBase* agi);
};
