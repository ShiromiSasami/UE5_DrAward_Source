// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_AwardBase.generated.h"

/**
* �A���[�h�̊��N���X
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
	/// �w�b�h���C�g�̐F�ݒ�
	/// </summary>
	/// <param name="color">�F</param>
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
	//�����Q�ƃI�u�W�F�N�g(�R���|�[�l���g)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr <class USpringArmComponent> _springArm = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr <class UCameraComponent> _camera = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr <class UPointLightComponent> _topLight = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr <class USpotLightComponent> _headLight = nullptr;

	//�ϓ��p�����[�^
	bool bDead;

	//�Œ�p�����[�^
	const float LIFE_SPAN = 3.f;
};
