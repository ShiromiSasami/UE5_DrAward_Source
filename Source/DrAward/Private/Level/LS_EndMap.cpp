// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LS_EndMap.h"

#include "GameInstance/C_AwardGameInstanceBase.h"
#include "Other/C_DrAwardSaveGameBase.h"
#include "Other/C_TorchBase.h"
#include "Character/C_AwardBase.h"
#include "Other/AwardScoreStruct.h"

#include <Kismet/GameplayStatics.h>
#include <NiagaraActor.h>
#include <NiagaraComponent.h>
#include <Blueprint/UserWidget.h>


ALS_EndMap::ALS_EndMap()
{

}

void ALS_EndMap::BeginPlay()
{
    Super::BeginPlay();

    if (const auto awardGameInstance = Cast<UC_AwardGameInstanceBase>(GetGameInstance()))
    {
        Save(awardGameInstance);

        const auto world = GetWorld();
        TArray<AActor*> actors;
        if (awardGameInstance->IsClear)
        {
            UGameplayStatics::GetAllActorsOfClass(world, ANiagaraActor::StaticClass(), actors);
            for (auto i = 0; i < actors.Num(); i++)
            {
                if (const auto ns = Cast<ANiagaraActor>(actors[i]))
                {
                    ns->GetComponentByClass(UNiagaraComponent::StaticClass())->SetActive(true);
                }
            }

            const FString ClearSoundPath = "/Script/Engine.SoundWave'/Game/Audio/game_clear.game_clear'";
            if (const auto clearSound = TSoftObjectPtr<USoundBase>(FSoftObjectPath(*ClearSoundPath)).LoadSynchronous())
            {
                UGameplayStatics::PlaySound2D(world, clearSound);
            }
        }
        else
        {
            if (const auto award = Cast<AC_AwardBase>(UGameplayStatics::GetPlayerCharacter(world, 1)))
            {
                award->SetLightColor(FColor(255, 0, 0));
            }

            UGameplayStatics::GetAllActorsOfClass(world, AC_TorchBase::StaticClass(), actors);
            for (auto i = 0; i < actors.Num(); i++)
            {
                if (auto torch = Cast<AC_TorchBase>(actors[i]))
                {
                    torch->SetColor(FColor(255, 0, 0));
                }
            }

            const FString OverSoundPath = "/Script/Engine.SoundWave'/Game/Audio/game_over.game_over'";
            if (const auto overSound = TSoftObjectPtr<USoundBase>(FSoftObjectPath(*OverSoundPath)).LoadSynchronous())
            {
                UGameplayStatics::PlaySound2D(world, overSound);
            }
        }
    }

    const FString WidgetPath = "/Script/UMGEditor.WidgetBlueprint'/Game/BP/UI/BP_EndWidget.BP_EndWidget_c'";
    if (const auto WidgetClass = TSoftClassPtr<UUserWidget>(FSoftClassPath(*WidgetPath)).LoadSynchronous())
    {
        CreateWidget<UUserWidget>(GetWorld(), WidgetClass)->AddToViewport();
    }

    if (const auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        controller->SetShowMouseCursor(true);
    }
}

void ALS_EndMap::Save(UC_AwardGameInstanceBase* agi)
{
    if (!agi) return;
    //Score‚ÌStageŠK‚Ì•Û‘¶
    FString stageName = agi->StageName;
    int8 startIndex = 5;
    FString numText = stageName.Mid(startIndex, stageName.Len() - startIndex);

    //¡‰ñ‚ÌScore‚ð\‘¢‘Ì‚É‚·‚é
    FAwardScoreStruct nowScore;
    nowScore.StageNum = FCString::Atoi(*numText);
    //Score‚ÌŽžŠÔ‚Ì•Û‘¶
    nowScore.MinuteNum = agi->Minute;
    nowScore.SecondNum = agi->Second;
    float nowScoreTime = nowScore.MinuteNum * 60 + nowScore.SecondNum;

    bool isAdded = false;
    TArray<FAwardScoreStruct> tempScores;
    //Œ»ó‚Ì\‘¢‘Ì”z—ñ‚ðŽæ“¾
    auto save = agi->GetSaveData();
    TArray<FAwardScoreStruct> scores = save->AwardScores;
    for (auto score : scores)
    {
        if(isAdded) 
        { 
            tempScores.Add(score);
            continue;
        }

        if(score.StageNum < nowScore.StageNum)
        {
            tempScores.Add(nowScore);
            isAdded = true;
        }
        if (score.StageNum == nowScore.StageNum) 
        {
            float scoreTime = score.MinuteNum * 60 + score.SecondNum;
            if (scoreTime > nowScoreTime)
            {
                tempScores.Add(nowScore);
                isAdded = true;
            }
        }

        tempScores.Add(score);
    }

    if (!isAdded)
    {
        tempScores.Add(nowScore);
    }

    save->AwardScores = tempScores;

    UGameplayStatics::SaveGameToSlot(save, agi->GetSaveSlotName(), 0);
    agi->IsSaveDataAvailable = true;
}
