// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Other/AwardBlueprintFunctionLibrary.h"
#include "DrAwardGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoadStreamLevelCompleteSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnloadStreamLevelCompleteSignature);

/**
 * �A���[�h�̃Q�[�����[�h���N���X
 */
UCLASS()
class DRAWARD_API ADrAwardGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADrAwardGameModeBase();

protected:
#pragma region OverrideFunction

	virtual void BeginPlay() override;

#pragma endregion

protected:
#pragma region DelegateBindFunction

	/// <summary>
	/// PlayerDestory�̃o�C���h�֐�
	/// </summary>
	/// <param name="Actor">�폜���ꂽ�A�N�^�[</param>
	/// ��OnPawnEndPlay(AActor* actor, EEndPlayReason::Type endPlayReason)��{���͎g�p���ׂ�
	UFUNCTION()
	void OnDestroyed(class AActor* Actor);

	/// <summary>
	/// LoadStreamLevelComplete�̃o�C���h�֐�
	/// </summary>
	UFUNCTION()
	void LoadStreamLevelComplete();

	/// <summary>
	/// UnloadStreamLevelComplete�̃o�C���h�֐�
	/// </summary>
	UFUNCTION()
	void UnloadStreamLevelComplete();

	/// <summary>
	/// Load������ɑO��Stage��Unload����
	/// </summary>
	UFUNCTION()
	void PreviousStageUnload();

#pragma endregion

#pragma region LevelFunction

	/// <summary>
	/// ���x���̓ǂݍ���
	/// </summary>
	/// <param name="level">���x���̖��O</param>
	void LoadLevel(const FName& level);

	/// <summary>
	/// ���x���̉��
	/// </summary>
	/// <param name="level">���x���̖��O</param>
	void UnloadLevel(const FName& level);

#pragma endregion

	/// <summary>
	/// �v���C���[�폜�C�x���g��OnDestroyed��R�Â��ݒ�
	/// </summary>
	void SetPlayerDestroyDelegate();

	/// <summary>
	/// UI�̃C���X�^���X����
	/// </summary>
	void CreateUIWidget();

	/// <summary>
	/// �Q�[���C���X�^���X�̏�����
	/// </summary>
	void InitGameInstance();

	/// <summary>
	/// ���Ԃ̃J�E���g�A�b�v(UI�\������)
	/// </summary>
	void TimeCountUp();

	/// <summary>
	/// �`���[�g���A��UI�̕\��
	/// </summary>
	void ShowTutorialUI() const;

public:
	//���J�f���Q�[�g
#pragma region Delegate

	/// <summary>
	/// ���x���ǂݍ��݊������̃C�x���g
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Level")
	FLoadStreamLevelCompleteSignature OnLoadStreamLevelCompleted;

	/// <summary>
	/// ���x������������̃C�x���g
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Level")
	FUnloadStreamLevelCompleteSignature OnUnloadStreamLevelCompleted;

#pragma endregion

	/// <summary>
	/// ����Stage�ֈڍs
	/// </summary>
	void NextStage();

	//�o�ߎ��Ԃ̐ݒ�

	/// <summary>
	/// ���Ԍo�ߏ����̊J�n
	/// </summary>
	FORCEINLINE void StartTimeCount() { bIsTimeCountEnabled = true; };

	/// <summary>
	/// ���Ԍo�ߏ����̒�~
	/// </summary>
	FORCEINLINE void StopTimeCount() { bIsTimeCountEnabled = false; };

protected:
	TObjectPtr<class UC_AwardGameInstanceBase> _agi;
	TObjectPtr<class UUserWidget> _loadingWidget;
	TObjectPtr<class UAudioComponent> _stairSound;

	FLatentActionInfo LoadLatentAction;
	FLatentActionInfo UnloadLatentAction;

	int _nowStageNum;
	bool bIsTimeCountEnabled;
};
