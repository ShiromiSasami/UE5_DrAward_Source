// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Other/AwardBlueprintFunctionLibrary.h"
#include "Other/AwardScoreStruct.h"
#include "C_DrAwardSaveGameBase.generated.h"

/**
 * セーブデータ格納クラス
 */
UCLASS()
class DRAWARD_API UC_DrAwardSaveGameBase : public USaveGame
{
	GENERATED_BODY()
public:
	UC_DrAwardSaveGameBase();
	
public:

	Property<TArray<FAwardScoreStruct>> AwardScores
	{
		_awardScores,
		[this](TArray<FAwardScoreStruct> value) { _awardScores = value; },
		[this]() { return _awardScores; }
	};


private:
	UPROPERTY(EditAnywhere)
	TArray<FAwardScoreStruct> _awardScores;
};
