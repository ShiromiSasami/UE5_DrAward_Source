// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_TrapRockBase.generated.h"

/**
 * トラップ岩の基礎クラス
 */
UCLASS()
class DRAWARD_API AC_TrapRockBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_TrapRockBase();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void EndHaleWallCollisionBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& Hit
	);

	/// <summary>
	/// 岩のスポーン処理
	/// </summary>
	void SpawnRock();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USceneComponent> _root;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> _startMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UArrowComponent> _arrow;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> _endMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(MakeEditWidget = true))
	FVector _endHoleLocation;

	inline static float ROCK_LIFE_SPAN = 1.f;
	inline static float NEXT_SPAWN_SPAN = 3.f;
};
