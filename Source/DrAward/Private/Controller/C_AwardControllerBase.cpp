// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/C_AwardControllerBase.h"

#include <InputMappingContext.h>
#include <EnhancedInputComponent.h>
#include <InputTriggers.h>
#include <EnhancedInputSubsystems.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/KismetSystemLibrary.h>


AC_AwardControllerBase::AC_AwardControllerBase()
	: _imc(LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/Input/IMC_Award.IMC_Award"))),
	_inputMove(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_Move.IA_Move")))
{
}

void AC_AwardControllerBase::BeginPlay()
{
	Super::BeginPlay();

	SetupInput();
}

//エンハンスインプットの設定
void AC_AwardControllerBase::SetupInput()
{
	EnableInput(this);

	if (!InputComponent || !_inputMove || !_imc) return;
	if (auto eic = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		eic->BindAction(_inputMove, ETriggerEvent::Triggered, this, &AC_AwardControllerBase::MoveAction);
	}

	if (auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		subsystem->AddMappingContext(_imc, 0);
	}
}

void AC_AwardControllerBase::MoveAction(const FInputActionValue& value)
{
	if (auto character = GetCharacter())
	{
		auto vec = value.Get<FVector2D>();
		character->AddMovementInput(FVector(1.f, 0.f, 0.f), vec.X);
		character->AddMovementInput(FVector(0.f, 1.f, 0.f), vec.Y);
	}
}
