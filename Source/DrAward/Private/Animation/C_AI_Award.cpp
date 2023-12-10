// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/C_AI_Award.h"
#include "GameInstance/C_AwardGameInstanceBase.h"

#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>


UC_AI_Award::UC_AI_Award()
	:_speed(0.f),
	_isClear(false),
	_endAnim(false)
{
   
}

void UC_AI_Award::NativeBeginPlay()
{
    _character = Cast<ACharacter>(GetOwningActor());
}

void UC_AI_Award::NativeInitializeAnimation()
{
    const auto world = GetWorld();
    const auto gameInstance = UGameplayStatics::GetGameInstance(world);
    if (const auto awardGameInstance = Cast<UC_AwardGameInstanceBase>(gameInstance))
    {
        _isClear = awardGameInstance->IsClear;
    }

    const auto levelName = world->GetMapName();
    //“ª‚É‚ ‚é UEDPEI_[number]_[MapName] ‚ð•ªŠ„
    FJsonSerializableArray strArray;
    levelName.ParseIntoArray(strArray, TEXT("_"));
    if (strArray.Num() < 3) { return; }
    _endAnim = (strArray[2] == "End") ? true : false;
}

void UC_AI_Award::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (_character != nullptr)
    {
        _speed = _character->GetVelocity().Size();
    }
}
