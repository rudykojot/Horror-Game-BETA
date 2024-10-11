// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "HorrorCharacter.generated.h"

UCLASS()
class VAROU_API AHorrorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHorrorCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* PlayerMapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* ShootAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* InteractionAction;

	void Run(const FInputActionValue& Value);

	void Interaction(const FInputActionValue& Value);

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
	
	UPROPERTY(VisibleAnywhere)
	class UPawnMovementComponent* MovementComponent;

private:

	APlayerController* PlayerController;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	float MaxStamina = 100;

	UPROPERTY(VisibleAnywhere)
	float Stamina;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float StaminaDrainRate = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float StaminaRecoverRate = 5.0f; 

public:	

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool IsRunning = false;
	
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;
	
	UFUNCTION(BlueprintPure)
	float GetStaminaPercent() const;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	float LookRate = 70.f;
};
