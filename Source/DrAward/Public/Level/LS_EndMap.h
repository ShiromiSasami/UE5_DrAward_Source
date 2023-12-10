// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LS_EndMap.generated.h"

/**
 * �G���h���x���p�̃��x���X�N���v�g
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
	/// /Score�p�̃f�[�^�ۑ�
	/// </summary>
	/// <param name="agi">�Q�[���C���X�^���X</param>
	void Save(class UC_AwardGameInstanceBase* agi);
};
