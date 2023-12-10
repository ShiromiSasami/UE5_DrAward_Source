// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_RockBase.generated.h"

/**
 * 岩の基礎クラス
 */
UCLASS()
class DRAWARD_API AC_RockBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_RockBase();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void CollisionBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& Hit
	);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> _mesh = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> _audio = nullptr;

	//固定パラメータ
	inline static float ATTACK_POWER = 100.f;
};
