// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/C_TrapArrowBase.h"

#include "Other/AwardBlueprintFunctionLibrary.h"

#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/AudioComponent.h>

AC_TrapArrowBase::AC_TrapArrowBase()
	:_floorMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"))),
	_arrowMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"))),
	_arrowCollision(CreateDefaultSubobject<UBoxComponent>(TEXT("ArrowCollision"))),
	_audio(CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"))),
	_arrowMoveTimeline(new FTimeline()),
	bIsPlayedSound(false)
{
	PrimaryActorTick.bCanEverTick = true;

	//メッシュの設定
	if (const auto fMeshData = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Mesh/trap_floor.trap_floor")))
	{
		_floorMesh->SetStaticMesh(fMeshData);
	}

	if(const auto aMeshData = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Mesh/trap_arrow.trap_arrow")))
	{
		_arrowMesh->SetStaticMesh(aMeshData);
	}
	_arrowMesh->SetupAttachment(_floorMesh);
	_arrowMesh->SetCollisionProfileName("InvisibleWall");

	//槍のコリジョン設定
	_arrowCollision->SetRelativeLocation(FVector(0.f, 0.f, -50.f));
	_arrowCollision->SetRelativeScale3D(FVector(3.f, 3.f, 1.5f));
	_arrowCollision->SetCollisionProfileName("NormalPreset");
	_arrowCollision->SetupAttachment(_arrowMesh);
	
	//槍移動Timeline設定
	_arrowMoveTimeline->SetTimelineLength(MOVE_COUNT);
	if (const auto TurnAroudCurve = LoadObject<UCurveFloat>(NULL, TEXT("/Game/Curve/TrapArrowMoveCurve.TrapArrowMoveCurve"))) 
	{
		FOnTimelineFloat ArrowMoveTimelineStepFunc;
		ArrowMoveTimelineStepFunc.BindUFunction(this, "ArrowMoveTimelineStep");
		_arrowMoveTimeline->AddInterpFloat(TurnAroudCurve, ArrowMoveTimelineStepFunc);
	}
	_arrowMoveTimeline->SetLooping(true);

	//音の設定
	if (const auto sound = LoadObject<USoundBase>(NULL, TEXT("/Game/Audio/trap_arrow.trap_arrow")))
	{
		_audio->Sound = sound;
	}
	_audio->SetupAttachment(_arrowMesh);
	_audio->bOverrideAttenuation = true;
	_audio->AttenuationOverrides.BinauralRadius = 80.f;
	_audio->AttenuationOverrides.FalloffDistance = 300.f;
	_audio->bAutoActivate = false;
}

AC_TrapArrowBase::~AC_TrapArrowBase()
{
	if (_arrowMoveTimeline)
	{
		_arrowMoveTimeline->Stop();
		delete _arrowMoveTimeline;
		_arrowMoveTimeline = nullptr;
	}
}

void AC_TrapArrowBase::BeginPlay()
{
	Super::BeginPlay();
	
	_arrowCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_TrapArrowBase::CollisionBeginOverlap);

	_arrowMoveTimeline->PlayFromStart();
}

void AC_TrapArrowBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateArrowMove(DeltaTime);
}

void AC_TrapArrowBase::CollisionBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& Hit)
{
	UAwardBlueprintFunctionLibrary::DamageAward(OtherActor, ATTACK_POWER);
}

void AC_TrapArrowBase::UpdateArrowMove(float DeltaTime)
{
	_arrowMoveTimeline->TickTimeline(DeltaTime);
}

void AC_TrapArrowBase::ArrowMoveTimelineStep(float value)
{
	_arrowMesh->SetRelativeLocation(FVector(0.f, 0.f, value));

	if (_audio)
	{
		if (value >= 80.f && !bIsPlayedSound)
		{
			_audio->Play();
			bIsPlayedSound = true;
		}
		else if (value == 0.f)
		{
			bIsPlayedSound = false;
		}
	}
	
}

