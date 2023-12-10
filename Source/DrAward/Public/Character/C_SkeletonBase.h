// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "C_SkeletonBase.generated.h"

/**
* スケルトンの基底クラス
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
	//コリジョンイベント
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
	/// 方向転換の経過時間更新
	/// </summary>
	/// <param name="DeltaTime">経過時間</param>
	void TurnAround(float DeltaTime);

	/// <summary>
	/// 方向転換のタイムライン更新イベント
	/// </summary>
	/// <param name="value">Yaw軸の角度値</param>
	UFUNCTION()
	void TurnAroundTimelineStep(float value);

	/// <summary>
	/// 方向転換完了イベント
	/// </summary>
	UFUNCTION()
	FORCEINLINE void TurnAroundTimelineFinished() { bTurning = false; };

public:
	/// <summary>
	/// 回転中かどうか判断
	/// </summary>
	/// <returns>回転中の有無</returns>
	FORCEINLINE bool IsTurning() const{ return bTurning;}

protected:
	//保持する構造体・コンポーネント
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USkeletalMeshComponent> _mesh = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UCapsuleComponent> _collision = nullptr;

	FTimeline* _turnAroundTimeline;

	//変動パラメータ
	bool bTurning;
	double _beforeYaw;

	//固定パラメータ
	const float TURN_AROUND_COUNT = 3.f;
	const float ATTACK_POWER = 100.f;
};
