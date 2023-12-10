


// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/AwardBlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Character/C_AwardBase.h"

#include <sstream>

float UAwardBlueprintFunctionLibrary::GetTargetAngle(const FVector tNormal, const FVector fNormal, const FVector uNormal)
{
	auto xDot = FVector::DotProduct(tNormal, fNormal);
	auto angle = UKismetMathLibrary::DegAcos(xDot);
	auto cross = FVector::CrossProduct(tNormal, fNormal);
	auto yDot = FVector::DotProduct(cross, uNormal);
	auto sign = (yDot < 0.f) ? 1.f : -1.f;
	return angle * sign;
}

bool UAwardBlueprintFunctionLibrary::DamageAward(AActor* actor, const float damage)
{
	if (auto award = Cast<AC_AwardBase>(actor))
	{
		UGameplayStatics::ApplyDamage(award, damage, nullptr, nullptr, UDamageType::StaticClass());
		return true;
	}
	
	return false;
}

FString UAwardBlueprintFunctionLibrary::CastIntToFString(const int value, const uint8 digit)
{
	FString outputString = FString::Printf(TEXT("%0*d"), digit, value);
	return outputString;
}

