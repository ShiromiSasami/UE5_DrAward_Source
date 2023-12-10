

#include "Other/C_TorchBase.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Components/PointLightComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AC_TorchBase::AC_TorchBase()
	: _mesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"))),
	_npsFire(CreateDefaultSubobject<UNiagaraComponent>(TEXT("NPS_Fire"))),
	_lightSource(CreateDefaultSubobject<UPointLightComponent>(TEXT("LightSource"))),
	_audio(CreateDefaultSubobject<UAudioComponent>(TEXT("Audio")))
{
	PrimaryActorTick.bCanEverTick = false;

	//メッシュの設定
	if (const auto meshData = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Mesh/torch.torch")))
	{
		_mesh->SetStaticMesh(meshData);
	}

	//FXの設定
	if (const auto fire = LoadObject<UNiagaraSystem>(NULL, TEXT("/Game/FX/NS_Fire.NS_Fire")))
	{
		_npsFire->SetAsset(fire);
		_npsFire->SetRelativeLocationAndRotation(FVector(0.f, -50.f, 20.f), FRotator(0.f, 0.f, -90.f));
		if (_mesh)
		{
			_npsFire->SetupAttachment(_mesh);
		}
	}

	//ライトの設定
	_lightSource->SetRelativeLocationAndRotation(FVector(0.f, -50.f, 70.f), FRotator(0.f, 0.f, -90.f));
	_lightSource->Intensity = 100.f;
	_lightSource->AttenuationRadius = 300.f;
	_lightSource->SetCastShadows(false);
	_lightSource->SetupAttachment(_mesh);

	//音の設定
	if (const auto sound = LoadObject<USoundBase>(NULL, TEXT("/Game/Audio/fire.fire")))
	{
		_audio->Sound = sound;
	}
	_audio->SetRelativeLocation(FVector(0.f, -50.f, 25.f));
	_audio->SetupAttachment(_mesh);
	_audio->bOverrideAttenuation = true;
	_audio->AttenuationOverrides.BinauralRadius = 50.f;
	_audio->AttenuationOverrides.FalloffDistance = 200.f;
}

void AC_TorchBase::OnConstruction(const FTransform& Transform)
{
	if (IS_GOAL)
	{
		SetColor(FColor(0, 0, 255));
	}
}

void AC_TorchBase::SetColor(FColor color)
{
	_lightSource->SetLightColor(color);
	_npsFire->SetColorParameter("User.FireColor", color);
}

