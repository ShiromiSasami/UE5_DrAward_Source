// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/C_SkeletonControllerBase.h"

#include "Character/C_SkeletonBase.h"
#include "GameMode/DrAwardGameModeBase.h"

#include <GameFramework/Character.h>


AC_SkeletonControllerBase::AC_SkeletonControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_SkeletonControllerBase::BeginPlay()
{
	Super::BeginPlay();

	_character = Cast<AC_SkeletonBase>(GetCharacter());

	if (const auto awardGameMode = Cast<ADrAwardGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		awardGameMode->OnLoadStreamLevelCompleted.AddDynamic(this, &AC_SkeletonControllerBase::LoadStreamLevelCompleted);
	}
}

void AC_SkeletonControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (_character && !_character->IsTurning())
	{
		const auto fowardVec = _character->GetActorForwardVector();
		_character->AddMovementInput(fowardVec);
	}
}

void AC_SkeletonControllerBase::LoadStreamLevelCompleted()
{
	if (!_character)
	{
		_character = Cast<AC_SkeletonBase>(GetCharacter());
	}
}
