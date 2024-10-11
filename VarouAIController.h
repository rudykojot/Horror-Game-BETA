// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "VarouAIController.generated.h"

/**
 * 
 */
UCLASS()
class VAROU_API AVarouAIController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;
	

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior; 
};
	