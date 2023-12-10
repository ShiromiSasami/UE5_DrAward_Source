// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_StairStart.generated.h"

/**
 * エリアスタートの階段
 */
UCLASS()
class DRAWARD_API AC_StairStart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_StairStart();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> _stairMesh = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> _roofMesh = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class USpotLightComponent> _spotLight = nullptr;
};
