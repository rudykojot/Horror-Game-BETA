// Fill out your copyright notice in the Description page of Project Settings.


#include "VarouAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HorrorCharacter.h"


void AVarouAIController::BeginPlay()
{
    Super::BeginPlay(); 

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

    }
}

void AVarouAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


