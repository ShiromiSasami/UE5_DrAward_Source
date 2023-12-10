// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_SkeletonBase.h"

#include "Other/AwardBlueprintFunctionLibrary.h"

#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AC_SkeletonBase::AC_SkeletonBase()
	:_turnAroundTimeline(new FTimeline()),
	bTurning(false)
{
	PrimaryActorTick.bCanEverTick = true;

	//メッシュのデフォルト設定
	const auto mesh = GetMesh();
	if (const auto MeshAsset = LoadObject<USkeletalMesh>(NULL, TEXT("/Game/Mesh/skeleton.skeleton")))
	{
		mesh->SetSkeletalMesh(MeshAsset);
		mesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -60.f), FRotator(0.f, -90.f, 0.f));
	}

	//AnimationInstanceClassの設定
	if (const auto ABPClass = LoadObject<UClass>(NULL, TEXT("/Game/BP/Animation/ABP_Skeleton.ABP_Skeleton_c")))
	{
		mesh->AnimClass = ABPClass;
	}

	//コリジョンのデフォルト設定
	const auto collision = GetCapsuleComponent();
	collision->SetCapsuleSize(60.f, 60.f);
	collision->SetRelativeLocation(FVector(20.f, 0.f, 0.f));
	collision->SetCollisionProfileName("NormalPreset");
	collision->SetGenerateOverlapEvents(true);

	//その他のパラメータ
	const auto movement = GetCharacterMovement();
	movement->MaxWalkSpeed = 100.f;
	movement->bOrientRotationToMovement = true;

	//AIControllerClassの設定
	if (const auto ControllerClass = LoadObject<UClass>(NULL, TEXT("/Game/BP/Controller/BP_SkeletonController.BP_SkeletonController_c")))
	{
		AIControllerClass = ControllerClass;
	}

	//回転Timeline設定
	_turnAroundTimeline->SetTimelineLength(TURN_AROUND_COUNT);
	if (const auto TurnAroudCurve = LoadObject<UCurveFloat>(NULL, TEXT("/Game/Curve/SkeletonTurnAroudCurve.SkeletonTurnAroudCurve")))
	{
		FOnTimelineFloat TurnAroudTimelineStepFunc;
		TurnAroudTimelineStepFunc.BindUFunction(this, "TurnAroundTimelineStep");
		_turnAroundTimeline->AddInterpFloat(TurnAroudCurve, TurnAroudTimelineStepFunc);
	}
	
	FOnTimelineEvent TurnAroudTimelineFinishedFunc;
	TurnAroudTimelineFinishedFunc.BindUFunction(this, "TurnAroundTimelineFinished");
	_turnAroundTimeline->SetTimelineFinishedFunc(TurnAroudTimelineFinishedFunc);
}

AC_SkeletonBase::~AC_SkeletonBase()
{
	if (_turnAroundTimeline)
	{
		_turnAroundTimeline->Stop();
		delete _turnAroundTimeline;
		_turnAroundTimeline = nullptr;
	}
}

void AC_SkeletonBase::BeginPlay()
{
	Super::BeginPlay();

	const auto collision = GetCapsuleComponent();
	collision->OnComponentHit.AddDynamic(this, &AC_SkeletonBase::CollisionHit);
	collision->OnComponentBeginOverlap.AddDynamic(this, &AC_SkeletonBase::CollisionBeginOverlap);
}

void AC_SkeletonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TurnAround(DeltaTime);
}

void AC_SkeletonBase::CollisionHit(
	UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
	)
{
	if (!_turnAroundTimeline->IsPlaying())
	{
		bTurning = true;
		_beforeYaw = GetActorRotation().Yaw;
		_turnAroundTimeline->PlayFromStart();
	}
}

void AC_SkeletonBase::CollisionBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& Hit
	)
{
	UAwardBlueprintFunctionLibrary::DamageAward(OtherActor, ATTACK_POWER);
}

void AC_SkeletonBase::TurnAround(float DeltaTime)
{
	if (_turnAroundTimeline->IsPlaying())
	{
		_turnAroundTimeline->TickTimeline(DeltaTime);
	}
}

void AC_SkeletonBase::TurnAroundTimelineStep(float value)
{
	auto rot = GetActorRotation();
	rot.Yaw = _beforeYaw + value;
	SetActorRelativeRotation(rot);
}
