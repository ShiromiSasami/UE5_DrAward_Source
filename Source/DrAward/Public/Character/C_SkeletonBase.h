// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "C_SkeletonBase.generated.h"

/**
* �X�P���g���̊��N���X
*/
UCLASS()
class DRAWARD_API AC_SkeletonBase : public ACharacter
{
	GENERATED_BODY()

public:
	AC_SkeletonBase();
	~AC_SkeletonBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	//�R���W�����C�x���g
	UFUNCTION()
	void CollisionHit(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

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
	/// �����]���̌o�ߎ��ԍX�V
	/// </summary>
	/// <param name="DeltaTime">�o�ߎ���</param>
	void TurnAround(float DeltaTime);

	/// <summary>
	/// �����]���̃^�C�����C���X�V�C�x���g
	/// </summary>
	/// <param name="value">Yaw���̊p�x�l</param>
	UFUNCTION()
	void TurnAroundTimelineStep(float value);

	/// <summary>
	/// �����]�������C�x���g
	/// </summary>
	UFUNCTION()
	FORCEINLINE void TurnAroundTimelineFinished() { bTurning = false; };

public:
	/// <summary>
	/// ��]�����ǂ������f
	/// </summary>
	/// <returns>��]���̗L��</returns>
	FORCEINLINE bool IsTurning() const{ return bTurning;}

protected:
	//�ێ�����\���́E�R���|�[�l���g
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USkeletalMeshComponent> _mesh = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UCapsuleComponent> _collision = nullptr;

	FTimeline* _turnAroundTimeline;

	//�ϓ��p�����[�^
	bool bTurning;
	double _beforeYaw;

	//�Œ�p�����[�^
	const float TURN_AROUND_COUNT = 3.f;
	const float ATTACK_POWER = 100.f;
};
