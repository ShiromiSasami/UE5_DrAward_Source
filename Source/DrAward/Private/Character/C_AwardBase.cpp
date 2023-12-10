// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_AwardBase.h"

#include "Kismet/KismetSystemLibrary.h"
#include "GameInstance/C_AwardGameInstanceBase.h"
#include "DrAward/DebugTools.h"
#include "Controller/C_AwardControllerBase.h"

#include <Components/CapsuleComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/PointLightComponent.h>
#include <Components/SpotLightComponent.h>
#include <Kismet/GameplayStatics.h>


// Sets default values
AC_AwardBase::AC_AwardBase()
	:_springArm(CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"))),
	_camera(CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"))),
	_topLight(CreateDefaultSubobject<UPointLightComponent>(TEXT("TopLight"))),
	_headLight(CreateDefaultSubobject<USpotLightComponent>(TEXT("HeadLight"))),
	bDead(false)
{
	PrimaryActorTick.bCanEverTick = false;

	//メッシュのデフォルト設定
	const auto mesh = GetMesh();
	const auto MeshAsset = LoadObject<USkeletalMesh>(NULL, TEXT("/Script/Engine.SkeletalMesh'/Game/Mesh/award.award'"));
	mesh->SetSkeletalMesh(MeshAsset);
	mesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -60.f), FRotator(0.f, -90.f, 0.f));

	//AnimationInstanceClassの設定
	if (const auto ABPClass = LoadClass<UAnimInstance>(NULL, TEXT("/Script/Engine.AnimBlueprint'/Game/BP/Animation/ABP_Award.ABP_Award_c'")))
	{
		mesh->AnimClass = ABPClass;
	}

	//コリジョンのデフォルト設定
	const auto collision = GetCapsuleComponent();
	collision->SetCapsuleSize(30.f, 60.f);
	collision->SetGenerateOverlapEvents(true);

	//その他パラメータ
	const auto movement = GetCharacterMovement();
	movement->MaxWalkSpeed = 300.f;
	movement->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	//カメラの生成
	_springArm->SetRelativeLocationAndRotation(FVector(-10.f, 0.f, 145.f), FRotator(-70.f, 0.f, 0.f));
	_springArm->TargetArmLength = 600.f;
	_springArm->bInheritYaw = false;
	_springArm->SetupAttachment(collision);
	_camera->SetupAttachment(_springArm);

	//ライト生成
	_topLight->SetRelativeLocation(FVector(0.f, 30.f, 90.f));
	_topLight->Intensity = 10.f;
	_topLight->AttenuationRadius = 300.f;
	_topLight->SetupAttachment(mesh);
	_headLight->Intensity = 30.f;
	_headLight->InnerConeAngle = 22.f;
	_headLight->OuterConeAngle = 44.f;
	_headLight->AttenuationRadius = 600.f;
	_headLight->SetupAttachment(mesh, FName("HeadLight"));
}

void AC_AwardBase::BeginPlay()
{
	Super::BeginPlay();
	
	const auto controller = GetWorld()->GetFirstPlayerController();
	controller->EnableInput(controller);

	if (const auto awardController = Cast<AC_AwardControllerBase>(controller))
	{
		awardController->SetAudioListenerOverride(_headLight,FVector::ZeroVector, FRotator::ZeroRotator);
	}

	Setup();
}

void AC_AwardBase::Setup()
{
	//ダメージデリゲート
	OnTakeAnyDamage.AddDynamic(this, &AC_AwardBase::TakeAnyDamage);
}

void AC_AwardBase::SetLightColor(const FColor color)
{
	_topLight->SetLightColor(color);
	_headLight->SetLightColor(color);
}

void AC_AwardBase::TakeAnyDamage(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigateBy,
	AActor* DamageCauser
	)
{
	if (Damage == 0) return;
	if (bDead) return;

	const FString DeathVoicePath = "/Script/Engine.SoundWave'/Game/Audio/death_voice.death_voice'";
	if (const auto DeathSoundAsset = TSoftObjectPtr<USoundBase>(FSoftObjectPath(*DeathVoicePath)).LoadSynchronous())
	{
		UGameplayStatics::PlaySound2D(GetWorld(), DeathSoundAsset);
	}

	bDead = true;
	GetCharacterMovement()->DisableMovement();
	const auto controller = GetWorld()->GetFirstPlayerController();
	controller->DisableInput(controller);

	const auto mesh = GetMesh();
	mesh->SetCollisionProfileName("Ragdoll");
	mesh->SetSimulatePhysics(true);

	if (const auto awardGameInstance = Cast<UC_AwardGameInstanceBase>(GetGameInstance()))
	{
		awardGameInstance->Life = awardGameInstance->Life - 1;
		if (awardGameInstance->Life <= 0)
		{
			awardGameInstance->IsClear = false;
			FTimerHandle handle;
			GetWorldTimerManager().SetTimer(handle, [this]{UGameplayStatics::OpenLevel(GetWorld(), "End"); }, LIFE_SPAN, false);
		}
		else
		{
			SetLifeSpan(LIFE_SPAN);
		}
	}
	
}

