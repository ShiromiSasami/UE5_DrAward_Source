// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_AwardBase.generated.h"

/**
* アワードの基底クラス
*/

UCLASS()
class DRAWARD_API AC_AwardBase : public ACharacter
{
	GENERATED_BODY()

public:
	AC_AwardBase();

protected:
	virtual void BeginPlay() override;
	virtual void Setup();

public:	
	/// <summary>
	/// ヘッドライトの色設定
	/// </summary>
	/// <param name="color">色</param>
	void SetLightColor(const FColor color);

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USkeletalMeshComponent> _mesh = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UCapsuleComponent> _collision = nullptr;

	UFUNCTION(BlueprintCallable)
	void TakeAnyDamage(
		AActor* DamagedActor,
		float Damage,
		const UDamageType* DamageType,
		AController* InstigateBy,
		AActor* DamageCauser
	);

protected:
	//所持参照オブジェクト(コンポーネント)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr <class USpringArmComponent> _springArm = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr <class UCameraComponent> _camera = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr <class UPointLightComponent> _topLight = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr <class USpotLightComponent> _headLight = nullptr;

	//変動パラメータ
	bool bDead;

	//固定パラメータ
	const float LIFE_SPAN = 3.f;
};
