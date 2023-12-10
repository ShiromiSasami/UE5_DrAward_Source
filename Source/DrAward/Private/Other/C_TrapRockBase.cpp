// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/C_TrapRockBase.h"

#include "Other/C_RockBase.h"

#include <Components/ArrowComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <Components/PrimitiveComponent.h>

// Sets default values
AC_TrapRockBase::AC_TrapRockBase()
	: _root(CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"))),
	_startMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HoleWallStartMesh"))),
	_arrow(CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"))),
	_endMesh(nullptr),
	_endHoleLocation(0.f, 200.f, 0.f)
{
	PrimaryActorTick.bCanEverTick = false;

	//ÉÅÉbÉVÉÖÇÃê›íË
	if (const auto meshData = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Mesh/hole_wall.hole_wall")))
	{
		_startMesh->SetStaticMesh(meshData);
	}
	_startMesh->SetupAttachment(_root);
	_startMesh->SetCollisionProfileName("InvisibleWall");
	_arrow->SetRelativeLocationAndRotation(FVector(-100.f, 0.f, 100.f), FRotator(0.f, 90.f, 0.f));
	_arrow->SetupAttachment(_startMesh);
}

void AC_TrapRockBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	auto rootLocation = _root->GetRelativeLocation();

	auto startRot = UKismetMathLibrary::FindLookAtRotation(rootLocation, _endHoleLocation + rootLocation) + FRotator(0.f, -90.f, 0.f);
	startRot = FRotator(startRot.Roll, startRot.Yaw, -startRot.Pitch);
	_startMesh->SetRelativeLocationAndRotation(startRot.RotateVector(FVector(100.f, 0.f, -100.f)), startRot.Quaternion());

	FTransform endTrans;
	auto endRot = UKismetMathLibrary::FindLookAtRotation(_endHoleLocation + rootLocation, rootLocation) + FRotator(0.f, -90.f, 0.f);
	endRot = FRotator(endRot.Roll, endRot.Yaw, -endRot.Pitch);
	endTrans.SetLocation(endRot.RotateVector(FVector(100.f, 0.f, -100.f)) + _endHoleLocation);
	endTrans.SetRotation(endRot.Quaternion());

	auto endMeshComp = AddComponentByClass(UStaticMeshComponent::StaticClass(), false, endTrans, false);
	_endMesh = Cast<UStaticMeshComponent>(endMeshComp);
	if (_endMesh)
	{
		_endMesh->SetupAttachment(_root);
		if (const auto meshData = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Mesh/hole_wall.hole_wall")))
		{
			_endMesh->SetStaticMesh(meshData);
		}
		_endMesh->SetCollisionProfileName("InvisibleWall");
	}
}

void AC_TrapRockBase::BeginPlay()
{
	Super::BeginPlay();

	_endMesh->OnComponentBeginOverlap.AddDynamic(this, &AC_TrapRockBase::EndHaleWallCollisionBeginOverlap);

	SpawnRock();
}

void AC_TrapRockBase::EndHaleWallCollisionBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, 
	bool bFromSweep,
	const FHitResult& Hit
	)
{
	if (const auto rock = Cast<AC_RockBase>(OtherActor))
	{
		rock->SetLifeSpan(ROCK_LIFE_SPAN);
		FTimerHandle handle;
		GetWorldTimerManager().SetTimer(handle, this, &AC_TrapRockBase::SpawnRock, NEXT_SPAWN_SPAN, false);
	}
}

void AC_TrapRockBase::SpawnRock()
{
	FString RockPath = "/Game/BP/Other/BP_Rock.BP_Rock_c";
	if (const auto bpRock = TSoftClassPtr<AC_RockBase>(FSoftClassPath(*RockPath)).LoadSynchronous())
	{
		FTransform arrowTrans = _arrow->GetComponentTransform();
		auto location = UKismetMathLibrary::TransformLocation(arrowTrans, FVector(-100.f, 0.f, -100.f));
		FTransform trans = UKismetMathLibrary::MakeTransform(location, arrowTrans.Rotator());
		auto rock = GetWorld()->SpawnActor<AC_RockBase>(bpRock, trans);
		TArray<UStaticMeshComponent*> components;
		rock->GetComponents<UStaticMeshComponent>(components);
		auto rockMesh = Cast<UStaticMeshComponent>(components[0]);
		rockMesh->SetSimulatePhysics(true);
		auto vec = UKismetMathLibrary::TransformDirection(arrowTrans, FVector(1000.f, 0.f, 0.f));
		rockMesh->AddImpulse(vec, FName("None"), true);
	}
}

