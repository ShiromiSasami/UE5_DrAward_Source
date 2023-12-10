// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LS_StartMap.h"

#include "UI/C_StartWidgetBase.h"

#include <Engine/StaticMeshActor.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/UserWidget.h>
#include <Blueprint/WidgetBlueprintLibrary.h>


ALS_StartMap::ALS_StartMap()
{
}

void ALS_StartMap::BeginPlay()
{
    Super::BeginPlay();

    const FString StartSoundPath = "/Script/Engine.SoundWave'/Game/Audio/start.start'";
    if (const auto startSound = TSoftObjectPtr<USoundBase>(FSoftObjectPath(*StartSoundPath)).LoadSynchronous())
    {
        UGameplayStatics::PlaySound2D(GetWorld(), startSound);
    }

    if (const auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        controller->SetShowMouseCursor(true);
    }

    const FString StartWidgetPath = "/Script/UMGEditor.WidgetBlueprint'/Game/BP/UI/BP_StartWidget.BP_StartWidget_c'";
    if (const auto StartWidgetClass = TSoftClassPtr<UUserWidget>(FSoftClassPath(*StartWidgetPath)).LoadSynchronous())
    {
        CreateWidget<UUserWidget>(GetWorld(), StartWidgetClass)->AddToViewport();
    }

    const FString ScoreBoardWidgetPath = "/Script/UMGEditor.WidgetBlueprint'/Game/BP/UI/BP_ScoreBoardWidget.BP_ScoreBoardWidget_c'";
    if (const auto ScoreBoardWidgetClass = TSoftClassPtr<UUserWidget>(FSoftClassPath(*ScoreBoardWidgetPath)).LoadSynchronous())
    {
        CreateWidget<UUserWidget>(GetWorld(), ScoreBoardWidgetClass)->AddToViewport();
    }

    TArray<UUserWidget*> widgets;
    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), widgets, UUserWidget::StaticClass());
    if (!widgets.IsEmpty())
    {
        for (auto widget : widgets)
        {
            if (widget->IsA<UC_StartWidgetBase>())
            {
                widget->SetVisibility(ESlateVisibility::Visible);
            }
            else
            {
                widget->SetVisibility(ESlateVisibility::Hidden);
            }
        }
    }
}
