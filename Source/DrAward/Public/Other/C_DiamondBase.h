// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "C_DiamondBase.generated.h"

/**
 * �_�C�������h�̊�b�N���X
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
	/// �s�b�N�A�b�v���o�^�C�����C���X�V�C�x���g
	/// </summary>
	/// <param name="value">��Ԃ̃u�����h�l</param>
	UFUNCTION()
	void PickupDirectionTimelineStep(float value);

	/// <summary>
	/// �N�A�b�v���o�^�C�����C���I���C�x���g
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

	//�Œ�p�����[�^
	inline static FFloat16 NORMAL_ROTATE_SPEED = 30.f;
	inline static FFloat16 PICKUP_ROTATE_SPEED = 360.f;
	inline static FFloat16 PICKUP_HEIGHT = 200.f;
};
