// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/C_TutorialWidgetBase.h"

#include "GameMode/DrAwardGameModeBase.h"

#include <Components/Button.h>
#include <UMG/Public/Animation/WidgetAnimation.h>
#include <UMG/Public/Animation/UMGSequencePlayer.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>

void UC_TutorialWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (Close_Btn)
	{
		Close_Btn->OnClicked.AddDynamic(this, &UC_TutorialWidgetBase::ClickedClose);
	}
}

bool UC_TutorialWidgetBase::Initialize()
{
	if (!Super::Initialize()) return false;

	if (TutorialAnimation)
	{
		if (const auto awardGameMode = Cast<ADrAwardGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			awardGameMode->StopTimeCount();
		}

		
		if (const auto character = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		{
			character->GetCharacterMovement()->DisableMovement();
		}
		PlayAnimation(TutorialAnimation, 0.f, 1);
	}

	return true;
}

void UC_TutorialWidgetBase::ClickedClose()
{
	if (TutorialAnimation)
	{
		PlayAnimation(TutorialAnimation, 0.f, 1, EUMGSequencePlayMode::Type::Reverse);
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(
			handle, 
			[this] 
			{
				if (const auto awardGameMode = Cast<ADrAwardGameModeBase>(GetWorld()->GetAuthGameMode()))
				{
					awardGameMode->StartTimeCount();
				}

				if (const auto character = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0)))
				{
					character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
				}
				RemoveFromParent();
			}, 
			TutorialAnimation->GetEndTime(), false
		);
		
	}
}
