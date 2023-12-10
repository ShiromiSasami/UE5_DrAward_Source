// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "C_DiamondBase.generated.h"

/**
 * ダイヤモンドの基礎クラス
 */

UCLASS()
class DRAWARD_API AC_DiamondBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_DiamondBase();
	~AC_DiamondBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

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
	/// <summary>
	/// ピックアップ演出タイムライン更新イベント
	/// </summary>
	/// <param name="value">補間のブレンド値</param>
	UFUNCTION()
	void PickupDirectionTimelineStep(float value);

	/// <summary>
	/// クアップ演出タイムライン終了イベント
	/// </summary>
	UFUNCTION()
	void PickupDirectionTimelineFinished();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> _mesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UPointLightComponent> _pointLight;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class URotatingMovementComponent> _rotatingMove;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UParticleSystemComponent> _glitter;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> _audio;

	FTimeline* _pickupDirectionTimeline;
	FVector _startLocation;

	//固定パラメータ
	inline static FFloat16 NORMAL_ROTATE_SPEED = 30.f;
	inline static FFloat16 PICKUP_ROTATE_SPEED = 360.f;
	inline static FFloat16 PICKUP_HEIGHT = 200.f;
};
