// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AwardBlueprintFunctionLibrary.generated.h"

//�v���p�e�B
template<class T> class Property
{
public:
    T& r;
    std::function<void(T value)> set = nullptr;
    std::function<T()> get = nullptr;

    operator T()
    {
        return get ? this->get() : this->r;
    }

    T operator ->()
    {
        return get ? this->get() : this->r;
    }

    void operator =(const T v)
    {
        if (set)
            this->set(v);
        else
            r = v;
    }
};

/**
* �u���[�v�����g�֐����C�u����
*/
UCLASS()
class DRAWARD_API UAwardBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/// <summary>
	/// �����̐i�s��������ɂ����^�[�Q�b�g�����̎擾
	/// </summary>
	/// <param name="tNormal">���K�����ꂽ�^�[�Q�b�g�����x�N�g��</param>
	/// <param name="fNormal">���K�����ꂽ�i�s�����x�N�g��</param>
	/// <param name="uNormal">���K�����ꂽ������x�N�g��</param>
	/// <returns>�p�x(�x���@)</returns>
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetTargetAngle(FVector tNormal, FVector fNormal, FVector uNormal);

	/// <summary>
	/// �A���[�h�ւ̃_���[�W����(�A���[�h�݂̂Ƀ_���[�W������܂�)
	/// </summary>
	/// <param name="actor">�A���[�h�A�N�^�[</param>
	/// <param name="damage">�^����_���[�W��</param>
	/// <returns>�����̐���/���s(����:true ���s:false)</returns>
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool DamageAward(AActor* actor, float damage);

    /// <summary>
    /// �����l���w�茅�\�L��FString�ɕϊ�
    /// </summary>
    /// <param name="value">�����l</param>
    /// <param name="digit">�w�茅</param>
    /// <returns>�ϊ�����������</returns>
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString CastIntToFString(const int value, const uint8 digit);
};
