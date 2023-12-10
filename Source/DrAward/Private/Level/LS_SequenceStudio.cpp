// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LS_SequenceStudio.h"

#include "GameInstance/C_AwardGameInstanceBase.h"

#include <Kismet/GameplayStatics.h>
#include <LevelSequencePlayer.h>
#include <LevelSequenceActor.h>


ALS_SequenceStudio::ALS_SequenceStudio()
{
}

void ALS_SequenceStudio::BeginPlay()
{
    for (TObjectIterator<ALevelSequenceActor> Itr; Itr; ++Itr)
    {
        ALevelSequenceActor* SequenceActor = *Itr;
        if (SequenceActor && SequenceActor->SequencePlayer)
        {
            SequenceActor->SequencePlayer->Play();
            FTimerHandle handle;
            GetWorldTimerManager().SetTimer(
                handle, 
                [this] {
                    auto agi = Cast<UC_AwardGameInstanceBase>(UGameplayStatics::GetGameInstance(GetWorld()));
                    float loadTime;
                    agi->Loading(loadTime);
                    FTimerHandle handle;
                    GetWorld()->GetTimerManager().SetTimer(handle, [this] {UGameplayStatics::OpenLevel(GetWorld(), "Start"); }, loadTime, false);
                },
                SequenceActor->SequencePlayer->GetDuration().AsSeconds() - 0.1f,
                false
            );
        }
    }
}
