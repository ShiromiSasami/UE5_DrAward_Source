// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_TorchBase.generated.h"

/**
 * トーチ基礎クラス
 */
UCLASS()
class DRAWARD_API AC_TorchBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_TorchBase();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	/// <summary>
	///	トーチの炎の色設定
	/// </summary>
	/// <param name="color">色</param>
	void SetColor(FColor color);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> _mesh = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> _npsFire = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UPointLightComponent> _lightSource = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> _audio = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IS_GOAL = false;
};
