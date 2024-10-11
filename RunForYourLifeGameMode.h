// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VarouGameModeBase.h"
#include "RunForYourLifeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VAROU_API ARunForYourLifeGameMode : public AVarouGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;

};

