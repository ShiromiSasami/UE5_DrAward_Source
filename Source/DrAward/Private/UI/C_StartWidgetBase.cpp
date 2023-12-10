// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_StartWidgetBase.h"

#include "GameInstance/C_AwardGameInstanceBase.h"
#include "UI/C_ScoreBoardWidgetBase.h"

#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/WidgetBlueprintLibrary.h>

void UC_StartWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();

    if (Start_Btn)
    {
        Start_Btn->OnClicked.AddDynamic(this, &UC_StartWidgetBase::ClickedStart);
    }

    if (Quit_Btn)
    {
        Quit_Btn->OnClicked.AddDynamic(this, &UC_StartWidgetBase::ClickedQuit);
    }

    if (BestScore_Btn)
    {
        BestScore_Btn->OnClicked.AddDynamic(this, &UC_StartWidgetBase::ClickedBestScore);
    }
}

void UC_StartWidgetBase::ClickedStart()
{
    if (const auto awardGameInstance = Cast<UC_AwardGameInstanceBase>(GetGameInstance()))
    {
        awardGameInstance->IsClear = true;
    }

    float loadTime;
    if (auto agi = Cast<UC_AwardGameInstanceBase>(UGameplayStatics::GetGameInstance(GetWorld())))
    {
        agi->Loading(loadTime);
        FTimerHandle handle;
        GetWorld()->GetTimerManager().SetTimer(handle, [this]{UGameplayStatics::OpenLevel(GetWorld(), "Main"); }, loadTime, false);
    }
}

void UC_StartWidgetBase::ClickedQuit()
{
    UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UC_StartWidgetBase::ClickedBestScore()
{
    this->SetVisibility(ESlateVisibility::Hidden);
    TArray<UUserWidget*> widgets;
    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), widgets, UC_ScoreBoard::StaticClass());
    if (!widgets.IsEmpty())
    {
        widgets[0]->SetVisibility(ESlateVisibility::Visible);
    }
}
