#pragma once

#include "CoreMinimal.h"
#include "AwardScoreStruct.generated.h"

/**
 * ScoreÇÃç\ë¢ëÃ
 */
USTRUCT(BlueprintType)
struct FAwardScoreStruct
{
	GENERATED_BODY()

	FORCEINLINE FAwardScoreStruct();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StageNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinuteNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SecondNum = 0;

};

FORCEINLINE FAwardScoreStruct::FAwardScoreStruct()
{
}

