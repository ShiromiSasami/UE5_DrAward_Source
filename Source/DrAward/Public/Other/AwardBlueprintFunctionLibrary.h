// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AwardBlueprintFunctionLibrary.generated.h"

//プロパティ
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
* ブループリント関数ライブラリ
*/
UCLASS()
class DRAWARD_API UAwardBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/// <summary>
	/// 自分の進行方向を基準にしたターゲット方向の取得
	/// </summary>
	/// <param name="tNormal">正規化されたターゲット方向ベクトル</param>
	/// <param name="fNormal">正規化された進行方向ベクトル</param>
	/// <param name="uNormal">正規化された上方向ベクトル</param>
	/// <returns>角度(度数法)</returns>
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetTargetAngle(FVector tNormal, FVector fNormal, FVector uNormal);

	/// <summary>
	/// アワードへのダメージ処理(アワードのみにダメージが入ります)
	/// </summary>
	/// <param name="actor">アワードアクター</param>
	/// <param name="damage">与えるダメージ量</param>
	/// <returns>処理の成功/失敗(成功:true 失敗:false)</returns>
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static bool DamageAward(AActor* actor, float damage);

    /// <summary>
    /// 整数値を指定桁表記のFStringに変換
    /// </summary>
    /// <param name="value">整数値</param>
    /// <param name="digit">指定桁</param>
    /// <returns>変換した文字列</returns>
    UFUNCTION(BlueprintCallable, BlueprintPure)
    static FString CastIntToFString(const int value, const uint8 digit);
};
