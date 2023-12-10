// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/C_StairGoal.h"

#include "GameMode/DrAwardGameModeBase.h"
#include "GameInstance/C_AwardGameInstanceBase.h"
#include "Character/C_AwardBase.h"

#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
AC_StairGoal::AC_StairGoal()
	:_mesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"))),
	_collision(CreateDefaultSubobject<UBoxComponent>(TEXT("GoalBox"))),
	bLastStage(false)
{
	PrimaryActorTick.bCanEverTick = false;

	//メッシュの設定
	if (const auto stairMeshData = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Mesh/stair.stair")))
	{
		_mesh->SetStaticMesh(stairMeshData);
	}

	//コリジョン設定
	_collision->SetRelativeLocation(FVector(-100.f, -100.f, -50.f));
	_collision->SetRelativeScale3D(FVector(3.f, 3.f, 1.f));
	_collision->SetupAttachment(_mesh);
	_collision->SetCollisionProfileName("NormalPreset");
}

void AC_StairGoal::BeginPlay()
{
	Super::BeginPlay();
	
	_collision->OnComponentBeginOverlap.AddDynamic(this, &AC_StairGoal::CollisionBeginOverlap);
}

void AC_StairGoal::CollisionBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& Hit
	)
{
	if (const auto award = Cast<AC_AwardBase>(OtherActor))
	{
		if (bLastStage)
		{
			const FString StairSoundPath = "/Script/Engine.SoundWave'/Game/Audio/stair.stair'";
			if (const auto stairSound = TSoftObjectPtr<USoundBase>(FSoftObjectPath(*StairSoundPath)).LoadSynchronous())
			{
				UGameplayStatics::SpawnSound2D(GetWorld(), stairSound);
			}

			if (const auto awardGameMode = Cast<ADrAwardGameModeBase>(GetWorld()->GetAuthGameMode()))
			{
				awardGameMode->StopTimeCount();
			}

			if (const auto movement = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetCharacterMovement())
			{
				movement->DisableMovement();
			}

			float loadTime = 1;
			if (const auto awardGameInstance = Cast<UC_AwardGameInstanceBase>(GetGameInstance()))
			{
				awardGameInstance->IsClear = true;
				awardGameInstance->Loading(loadTime);
			}
			FTimerHandle handle;
			GetWorld()->GetTimerManager().SetTimer(handle, [this] {UGameplayStatics::OpenLevel(GetWorld(), "End"); }, loadTime, false);
		}
		else
		{
			if (const auto awardGameMode = Cast<ADrAwardGameModeBase>(GetWorld()->GetAuthGameMode()))
			{
				awardGameMode->NextStage();
			}
		}
	}
}

