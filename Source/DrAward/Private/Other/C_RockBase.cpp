

#include "Other/C_RockBase.h"

#include "Other/AwardBlueprintFunctionLibrary.h"

#include <Kismet/GameplayStatics.h>
#include <Components/AudioComponent.h>

AC_RockBase::AC_RockBase()
	:_mesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RockMesh"))),
	_audio(CreateDefaultSubobject<UAudioComponent>(TEXT("Audio")))
{
	PrimaryActorTick.bCanEverTick = false;

	//ÉÅÉbÉVÉÖÇÃê›íË
	if (const auto meshData = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Mesh/rock.rock")))
	{
		_mesh->SetStaticMesh(meshData);
	}
	_mesh->SetCollisionProfileName("RockCollision");

	//âπÇÃê›íË
	if (const auto sound = LoadObject<USoundBase>(NULL, TEXT("/Game/Audio/rock.rock")))
	{
		_audio->Sound = sound;
	}
	_audio->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	_audio->SetupAttachment(_mesh);
	_audio->bOverrideAttenuation = true;
	_audio->AttenuationOverrides.BinauralRadius = 50.f;
	_audio->AttenuationOverrides.FalloffDistance = 300.f;
}

void AC_RockBase::BeginPlay()
{
	Super::BeginPlay();
	
	_mesh->OnComponentBeginOverlap.AddDynamic(this, &AC_RockBase::CollisionBeginOverlap);
}

void AC_RockBase::CollisionBeginOverlap(
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

