// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/C_StairStart.h"

#include <Components/SpotLightComponent.h>

// Sets default values
AC_StairStart::AC_StairStart()
	: _stairMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StairMesh"))),
	_roofMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoofMesh"))),
	_spotLight(CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight")))
{
	PrimaryActorTick.bCanEverTick = false;

	//ÉÅÉbÉVÉÖÇÃê›íË
	if (const auto stairMeshData = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Mesh/stair.stair")))
	{
		_stairMesh->SetStaticMesh(stairMeshData);
	}

	if (const auto roofMeshData = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Mesh/plane.plane")))
	{
		_roofMesh->SetStaticMesh(roofMeshData);
	}
	if (const auto roofMaterialData = LoadObject<UMaterialInterface>(NULL, TEXT("/Game/Material/M_Roof.M_Roof")))
	{
		_roofMesh->SetMaterial(0, roofMaterialData);
	}
	_roofMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 100.f), FRotator(0.f, 0.f, -90.f));
	_roofMesh->SetupAttachment(_stairMesh);

	_spotLight->SetupAttachment(_stairMesh);
	_spotLight->SetRelativeLocationAndRotation(FVector(0.f, -100.f, 100.f), FRotator(-45.f, 180.f, 0.f));
}

