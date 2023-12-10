// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_ScoreBoardWidgetBase.h"

#include "UI/C_StartWidgetBase.h"
#include "UI/C_ScoreWidgetBase.h"
#include "GameInstance/C_AwardGameInstanceBase.h"
#include "Other/AwardScoreStruct.h"
#include "Other/C_DrAwardSaveGameBase.h"
#include "DrAward/DebugTools.h"

#include <Components/Button.h>
#include <Components/VerticalBox.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

void UC_ScoreBoard::NativeConstruct()
{
    if (BackTitle_Btn)
    {
        BackTitle_Btn->OnClicked.AddDynamic(this, &UC_ScoreBoard::ClickedBackTitle);
    }
}

bool UC_ScoreBoard::Initialize()
{
    if (!Super::Initialize()) return false;

    if (ScoreBox)
    {
        const FString ScoreWidgetPath = "/Script/UMGEditor.WidgetBlueprint'/Game/BP/UI/BP_ScoreWidget.BP_ScoreWidget_c'";
        if (const auto ScoreWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*ScoreWidgetPath)).LoadSynchronous())
        {
            if (const auto agi = Cast<UC_AwardGameInstanceBase>(GetGameInstance()))
            {
                TArray<FAwardScoreStruct> scores = agi->GetSaveData()->AwardScores;
                for (int i = 0; i < scores.Num(); ++i )
                {
                    if (i > 2) break;
                    UUserWidget* widget = CreateWidget<UUserWidget>(this->GetWorld(), ScoreWidgetClass);
                    auto scoreWidget = Cast<UC_ScoreWidgetBase>(widget);
                    scoreWidget->Score = scores[i];
                    ScoreBox->AddChild(scoreWidget);
                }

                return false;
            }
        }
    }

    return false;
}

void UC_ScoreBoard::ClickedBackTitle()
{
    this->SetVisibility(ESlateVisibility::Hidden);
    TArray<UUserWidget*> widgets;
    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), widgets, UC_StartWidgetBase::StaticClass());
    if (!widgets.IsEmpty())
    {
        widgets[0]->SetVisibility(ESlateVisibility::Visible);
    }
}
