// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_NoPawnGameModeBase.generated.h"

/**
 * プレイヤー操作なしゲームモード基底クラス(Stageレベル以外で利用)
 */
UCLASS()
class DRAWARD_API AC_NoPawnGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AC_NoPawnGameModeBase();
};
