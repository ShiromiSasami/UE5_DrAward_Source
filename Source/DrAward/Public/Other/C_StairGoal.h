// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_StairGoal.generated.h"

/**
 * エリアゴールの階段
 */
UCLASS()
class DRAWARD_API AC_StairGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_StairGoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FORCEINLINE class UAudioComponent* GetStairAudio() const { return _stairAudio; };

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
	TObjectPtr<class UBoxComponent> _collision = nullptr;
	UPROPERTY(EditAnywhere)
	bool bLastStage;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> _stairAudio = nullptr;

};
