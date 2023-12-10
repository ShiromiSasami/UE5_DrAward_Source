// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "C_TrapArrowBase.generated.h"


/**
 * �g���b�v�̑��̊�b�N���X
 */
UCLASS()
class DRAWARD_API AC_TrapArrowBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_TrapArrowBase();
	~AC_TrapArrowBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

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

	/// <summary>
	/// ���̈ʒu�X�V
	/// </summary>
	/// <param name="DeltaTime"></param>
	void UpdateArrowMove(float DeltaTime);

	/// <summary>
	/// ���̈ړ��^�C�����C���X�V�C�x���g
	/// </summary>
	/// <param name="value">��ԃu�����h�l</param>
	UFUNCTION()
	void ArrowMoveTimelineStep(float value);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> _floorMesh = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> _arrowMesh = nullptr;	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> _arrowCollision = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> _audio = nullptr;

	FTimeline* _arrowMoveTimeline;

	bool bIsPlayedSound;

	//�Œ�p�����[�^
	inline static float ATTACK_POWER = 100.f;
	inline static float MOVE_COUNT = 10.f;
};
