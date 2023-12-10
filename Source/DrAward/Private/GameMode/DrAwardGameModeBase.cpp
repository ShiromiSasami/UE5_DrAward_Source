// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameMode/DrAwardGameModeBase.h"

#include "GameInstance/C_AwardGameInstanceBase.h"
#include "Character/C_AwardBase.h"
#include "DrAward/DebugTools.h"

#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <GameFramework/PlayerStart.h>
#include <Components/CapsuleComponent.h>
#include <Blueprint/UserWidget.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/AudioComponent.h>


ADrAwardGameModeBase::ADrAwardGameModeBase()
	:_stairSound(nullptr),
	_nowStageNum(1),
	bIsTimeCountEnabled(false)
{
	//デフォルト設定
	if (const auto PawnClass = LoadClass<AActor>(NULL, TEXT("/Game/BP/Character/BP_Award.BP_Award_c")))
	{
		DefaultPawnClass = PawnClass;
	}

	if (const auto ControllerClass = LoadClass<AActor>(NULL, TEXT("/Game/BP/Controller/BP_AwardController.BP_AwardController_c")))
	{
		PlayerControllerClass = ControllerClass;
	}

	//レベル読み込みアクションの設定
	LoadLatentAction.CallbackTarget = this;
	LoadLatentAction.ExecutionFunction = "LoadStreamLevelComplete";
	LoadLatentAction.UUID = 1;
	LoadLatentAction.Linkage = 0;

	UnloadLatentAction.CallbackTarget = this;
	UnloadLatentAction.ExecutionFunction = "UnloadStreamLevelComplete";
	UnloadLatentAction.UUID = 1;
	UnloadLatentAction.Linkage = 0;
}

void ADrAwardGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	OnLoadStreamLevelCompleted.AddDynamic(this, &ADrAwardGameModeBase::PreviousStageUnload);

	InitGameInstance();
	CreateUIWidget();

	LoadLevel(FName((FString)_agi->StageName));
	SetPlayerDestroyDelegate();

	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &ADrAwardGameModeBase::TimeCountUp, 1, true);

	const FString BGMPath = "/Script/Engine.SoundWave'/Game/Audio/bgm.bgm'";
	if (const auto BGMObj = TSoftObjectPtr<USoundBase>(FSoftObjectPath(*BGMPath)).LoadSynchronous())
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BGMObj);
	}

	if (!_agi->IsSaveDataAvailable)
	{
		ShowTutorialUI();
	}
	else
	{
		StartTimeCount();
	}
}

void ADrAwardGameModeBase::LoadLevel(const FName& level)
{
	if (const auto character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		const auto collision = character->GetCapsuleComponent();
		collision->SetGenerateOverlapEvents(false);
	}

	UGameplayStatics::LoadStreamLevel(this, level, true, true, LoadLatentAction);
}

void ADrAwardGameModeBase::UnloadLevel(const FName& level)
{
	UGameplayStatics::UnloadStreamLevel(this, level, UnloadLatentAction, true);
}

void ADrAwardGameModeBase::PreviousStageUnload()
{
	UnloadLevel(FName("Stage" + FString::FromInt(_nowStageNum - 1)));

	if (_nowStageNum <= 1) { return; }

	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, 
		[this]{
			if (_stairSound)
			{
				_stairSound->Stop();
				_stairSound = nullptr;
			}
			
			StartTimeCount();
			_loadingWidget->SetVisibility(ESlateVisibility::Hidden);
			if (auto character = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
			{
				character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			}
		},
		_agi->GetLoadingTime(), false);
}

void ADrAwardGameModeBase::NextStage()
{
	StopTimeCount();
	if (const auto character = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		character->GetCharacterMovement()->DisableMovement();
	}

	const FString StairSoundPath = "/Script/Engine.SoundWave'/Game/Audio/stair.stair'";
	if (const auto stairSound = TSoftObjectPtr<USoundBase>(FSoftObjectPath(*StairSoundPath)).LoadSynchronous())
	{
		_stairSound = UGameplayStatics::SpawnSound2D(GetWorld(), stairSound);
	}

	_loadingWidget->SetVisibility(ESlateVisibility::Visible);

	_nowStageNum++;
	_agi->StageName = "Stage" + FString::FromInt(_nowStageNum);
	LoadLevel(FName((FString)_agi->StageName));
}

void ADrAwardGameModeBase::OnDestroyed(AActor* Actor)
{
	if (const auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		RestartPlayer(controller);
		if (const auto character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			const auto start = FindPlayerStart(controller, (FString)_agi->StageName);
			character->SetActorTransform(start->GetTransform());
			SetPlayerDestroyDelegate();
		}
	}
}

void ADrAwardGameModeBase::LoadStreamLevelComplete()
{
	if (const auto character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (const auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			const auto start = FindPlayerStart(controller, (FString)_agi->StageName);
			character->SetActorTransform(start->GetTransform());
			const auto collision = character->GetCapsuleComponent();
			collision->SetGenerateOverlapEvents(true);
		}
	}

	if (OnLoadStreamLevelCompleted.IsBound())
	{ 
		OnLoadStreamLevelCompleted.Broadcast();
	}
}

void ADrAwardGameModeBase::UnloadStreamLevelComplete()
{
	if (OnUnloadStreamLevelCompleted.IsBound())
	{
		OnUnloadStreamLevelCompleted.Broadcast();
	}
}

void ADrAwardGameModeBase::SetPlayerDestroyDelegate()
{
	if (const auto pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		pawn->OnDestroyed.AddDynamic(this, &ADrAwardGameModeBase::OnDestroyed);
	}
}

void ADrAwardGameModeBase::CreateUIWidget()
{
	const FString WidgetPath = "/Script/UMGEditor.WidgetBlueprint'/Game/BP/UI/BP_PlayWidget.BP_PlayWidget_c'";
	if (const auto WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*WidgetPath)).LoadSynchronous())
	{ 
		CreateWidget<UUserWidget>(GetWorld(), WidgetClass)->AddToViewport();
	}

	float loadTime;
	UUserWidget* pLoadWidget;
	_agi->Loading(loadTime, &pLoadWidget);
	_loadingWidget = pLoadWidget;
	_loadingWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ADrAwardGameModeBase::InitGameInstance()
{
	_agi = Cast<UC_AwardGameInstanceBase>(GetGameInstance());
	if (_agi)
	{
		_agi->IsClear = false;
		_agi->Life = 2;
		_agi->ItemNum = 0;
		_agi->Minute = 0;
		_agi->Second = 0;
		_agi->StageName = "Stage1";
	}
}

void ADrAwardGameModeBase::TimeCountUp()
{
	if (!_agi) { return; }
	if (!bIsTimeCountEnabled) { return; }

	_agi->Second = _agi->Second + 1;
	if (_agi->Second % 60 == 0)
	{
		_agi->Second = 0;
		_agi->Minute = _agi->Minute + 1;
	}
}

void ADrAwardGameModeBase::ShowTutorialUI() const
{
	const FString WidgetPath = "/Script/UMGEditor.WidgetBlueprint'/Game/BP/UI/BP_TutorialWidget.BP_TutorialWidget_c'";
	if (const auto WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*WidgetPath)).LoadSynchronous()) 
	{
		CreateWidget<UUserWidget>(GetWorld(), WidgetClass)->AddToViewport();
	}

	if (const auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		controller->SetShowMouseCursor(true);
	}
}
