// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/C_DiamondBase.h"

#include "Character/C_AwardBase.h"
#include "GameInstance/C_AwardGameInstanceBase.h"

#include <Components/PointLightComponent.h>
#include <Components/AudioComponent.h>
#include <GameFramework/RotatingMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundCue.h>

// Sets default values
AC_DiamondBase::AC_DiamondBase()
	: _mesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DiamondMesh"))),
	_pointLight(CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"))),
	_rotatingMove(CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"))),
	_glitter(CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Glitter"))),
	_audio(CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"))),
	_pickupDirectionTimeline(new FTimeline())
{
	PrimaryActorTick.bCanEverTick = true;

	//メッシュの設定
	if (const auto meshData = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Mesh/diamond.diamond")))
	{
		_mesh->SetStaticMesh(meshData);
	}
	_mesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	_mesh->SetCollisionProfileName("NormalPreset");

	//ライトの設定
	_pointLight->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	_pointLight->Intensity = 10.f;
	_pointLight->AttenuationRadius = 100.f;
	_pointLight->SetupAttachment(_mesh);
	_pointLight->SetCastShadows(false);
	_pointLight->LightColor = FColor(245, 38, 255);

	//回転コンポーネントの設定
	_rotatingMove->RotationRate.Yaw = NORMAL_ROTATE_SPEED;

	//パーティクルの設定
	_glitter->SetupAttachment(_mesh);
	if (const auto particle = LoadObject<UParticleSystem>(NULL, TEXT("/Game/FX/PS_Glitter.PS_Glitter")))
	{
		_glitter->Template = particle;
	}

	//タイムラインの設定
	const FString PickupCurvePath = TEXT("/Game/Curve/DiamondPickupDirectionCurve.DiamondPickupDirectionCurve");
	if (const auto PickupDirectionCurve = LoadObject<UCurveFloat>(NULL, *PickupCurvePath))
	{
		FOnTimelineFloat PickupDirectionTimelineStepFunc;
		PickupDirectionTimelineStepFunc.BindUFunction(this, "PickupDirectionTimelineStep");
		_pickupDirectionTimeline->AddInterpFloat(PickupDirectionCurve, PickupDirectionTimelineStepFunc);
	}
	FOnTimelineEvent PickupDirectionTimelineFinishedFunc;
	PickupDirectionTimelineFinishedFunc.BindUFunction(this, "PickupDirectionTimelineFinished");
	_pickupDirectionTimeline->SetTimelineFinishedFunc(PickupDirectionTimelineFinishedFunc);

	//音の設定
	if (const auto sound = LoadObject<USoundCue>(NULL, TEXT("/Game/Audio/KirakiraCue.KirakiraCue")))
	{
		_audio->Sound = sound;
	}
	_audio->SetupAttachment(_mesh);
	_audio->bOverrideAttenuation = true;
	_audio->AttenuationOverrides.BinauralRadius = 50.f;
	_audio->AttenuationOverrides.FalloffDistance = 200.f;
}

AC_DiamondBase::~AC_DiamondBase()
{
	if (_pickupDirectionTimeline)
	{
		_pickupDirectionTimeline->Stop();
		delete _pickupDirectionTimeline;
		_pickupDirectionTimeline = nullptr;
	}
}

// Called when the game starts or when spawned
void AC_DiamondBase::BeginPlay()
{
	Super::BeginPlay();
	
	_mesh->OnComponentBeginOverlap.AddDynamic(this, &AC_DiamondBase::CollisionBeginOverlap);

}

// Called every frame
void AC_DiamondBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_pickupDirectionTimeline->IsPlaying())
	{
		_pickupDirectionTimeline->TickTimeline(DeltaTime);
	}
}

void AC_DiamondBase::CollisionBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& Hit)
{
	if (!OtherActor->IsA<AC_AwardBase>()) return;
	
	if (!_pickupDirectionTimeline->IsPlaying())
	{
		_startLocation = GetActorLocation();
		if (const auto gameInstance = Cast<UC_AwardGameInstanceBase>(GetGameInstance()))
		{
			gameInstance->ItemNum = gameInstance->ItemNum + 1;
			if (gameInstance->ItemNum % 3 == 0)
			{
				gameInstance->Life = gameInstance->Life + 1;
			}
		}
		_pickupDirectionTimeline->PlayFromStart();
	}
}

void AC_DiamondBase::PickupDirectionTimelineStep(float value)
{
	_rotatingMove->RotationRate.Yaw = UKismetMathLibrary::Lerp(NORMAL_ROTATE_SPEED, PICKUP_ROTATE_SPEED, value);
	auto nextVec = _startLocation;
	nextVec.Z += UKismetMathLibrary::Lerp(0, PICKUP_HEIGHT, value);
	SetActorLocation(nextVec);
}

void AC_DiamondBase::PickupDirectionTimelineFinished()
{
	if (const auto ps =  TSoftObjectPtr<UParticleSystem>(FSoftObjectPath("/Game/FX/PS_GlitterBurst.PS_GlitterBurst")).LoadSynchronous())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ps, GetActorTransform());
	}

	if (const auto sound = TSoftObjectPtr<USoundBase>(FSoftObjectPath("/Game/Audio/item_pickup.item_pickup")).LoadSynchronous())
	{
		UGameplayStatics::PlaySound2D(GetWorld(), sound);
	}

	Destroy();
}

