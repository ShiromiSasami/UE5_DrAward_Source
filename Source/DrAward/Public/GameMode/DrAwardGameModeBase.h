// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Other/AwardBlueprintFunctionLibrary.h"
#include "DrAwardGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoadStreamLevelCompleteSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnloadStreamLevelCompleteSignature);

/**
 * アワードのゲームモード基底クラス
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
	/// PlayerDestoryのバインド関数
	/// </summary>
	/// <param name="Actor">削除されたアクター</param>
	/// ※OnPawnEndPlay(AActor* actor, EEndPlayReason::Type endPlayReason)を本来は使用すべき
	UFUNCTION()
	void OnDestroyed(class AActor* Actor);

	/// <summary>
	/// LoadStreamLevelCompleteのバインド関数
	/// </summary>
	UFUNCTION()
	void LoadStreamLevelComplete();

	/// <summary>
	/// UnloadStreamLevelCompleteのバインド関数
	/// </summary>
	UFUNCTION()
	void UnloadStreamLevelComplete();

	/// <summary>
	/// Load完了後に前のStageをUnloadする
	/// </summary>
	UFUNCTION()
	void PreviousStageUnload();

#pragma endregion

#pragma region LevelFunction

	/// <summary>
	/// レベルの読み込み
	/// </summary>
	/// <param name="level">レベルの名前</param>
	void LoadLevel(const FName& level);

	/// <summary>
	/// レベルの解放
	/// </summary>
	/// <param name="level">レベルの名前</param>
	void UnloadLevel(const FName& level);

#pragma endregion

	/// <summary>
	/// プレイヤー削除イベントとOnDestroyedを紐づけ設定
	/// </summary>
	void SetPlayerDestroyDelegate();

	/// <summary>
	/// UIのインスタンス生成
	/// </summary>
	void CreateUIWidget();

	/// <summary>
	/// ゲームインスタンスの初期化
	/// </summary>
	void InitGameInstance();

	/// <summary>
	/// 時間のカウントアップ(UI表示時間)
	/// </summary>
	void TimeCountUp();

	/// <summary>
	/// チュートリアルUIの表示
	/// </summary>
	void ShowTutorialUI() const;

public:
	//公開デリゲート
#pragma region Delegate

	/// <summary>
	/// レベル読み込み完了時のイベント
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Level")
	FLoadStreamLevelCompleteSignature OnLoadStreamLevelCompleted;

	/// <summary>
	/// レベル解放完了時のイベント
	/// </summary>
	UPROPERTY(BlueprintReadWrite, Category = "Level")
	FUnloadStreamLevelCompleteSignature OnUnloadStreamLevelCompleted;

#pragma endregion

	/// <summary>
	/// 次のStageへ移行
	/// </summary>
	void NextStage();

	//経過時間の設定

	/// <summary>
	/// 時間経過処理の開始
	/// </summary>
	FORCEINLINE void StartTimeCount() { bIsTimeCountEnabled = true; };

	/// <summary>
	/// 時間経過処理の停止
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
