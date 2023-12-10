// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Other/AwardBlueprintFunctionLibrary.h"
#include "C_AwardGameInstanceBase.generated.h"

/**
 * �Q�[���C���X�^���X���N���X
 */
UCLASS()
class DRAWARD_API UC_AwardGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
public:
	UC_AwardGameInstanceBase();

private:
	virtual void Init() override;

public:
	/// <summary>
	/// ���[�f�B���O��ʂ̕\��
	/// </summary>
	/// <param name="loadingTime">���[�f�B���O����</param>
	/// <param name="widget">Widget���i�[����A�N�^�[(�|�C���^�̃|�C���^)</param>
	void Loading(float& loadingTime, UUserWidget** widget = nullptr) const;

public:
#pragma region Properties
	Property<bool> IsClear
	{
		bIsClear,
		[this](bool value) { bIsClear = value; },
		[this]() { return bIsClear; }
	};

	Property<int8> Life
	{
		_life,
		[this](int8 value) { _life = value; },
		[this]() { return _life; }
	};

	Property<int8> ItemNum
	{
		_itemNum,
		[this](int8 value) { _itemNum = value; },
		[this]() { return _itemNum; }
	};

	Property<int8> Minute
	{
		_timeMinute,
		[this](int8 value) { _timeMinute = value; },
		[this]() { return _timeMinute; }
	};

	Property<int8> Second
	{
		_timeSecond,
		[this](int8 value) { _timeSecond = value; },
		[this]() { return _timeSecond; }
	};

	Property<FString> StageName
	{
		_stageName,
		[this](FString value) { _stageName = value; },
		[this]() { return _stageName; }
	};

	Property<bool> IsSaveDataAvailable
	{
		bIsSaveDataAvailable,
		[this](bool value) { bIsSaveDataAvailable = value; },
		[this]() { return bIsSaveDataAvailable; }
	};

#pragma endregion

	/// <summary>
	/// ���[�f�B���O���Ԃ̎擾
	/// </summary>
	/// <returns>����(�b)</returns>
	FORCEINLINE float GetLoadingTime() const { return _loadingWaitTime; };

	/// <summary>
	/// �Z�[�u�f�[�^�̎擾
	/// </summary>
	/// <returns>�Q�[���f�[�^�I�u�W�F�N�g(C_DrAwardSaveGameBase)</returns> 
	FORCEINLINE class UC_DrAwardSaveGameBase* GetSaveData() const { return _saveData; };

	/// <summary>
	/// �Z�[�u�f�[�^�̃X���b�g���̎擾
	/// </summary>
	/// <returns>�X���b�g��</returns>
	FORCEINLINE FString GetSaveSlotName()const { return _saveSlotName; };

private:
#pragma region Variables for Properties
	bool bIsClear;
	int8 _life;
	int8 _itemNum;
	int8 _timeMinute;
	int8 _timeSecond;
	FString _stageName;
	bool bIsSaveDataAvailable;
#pragma endregion

	float _loadingWaitTime;
	UPROPERTY()
	TObjectPtr<class UC_DrAwardSaveGameBase> _saveData;
	FString _saveSlotName;
};
