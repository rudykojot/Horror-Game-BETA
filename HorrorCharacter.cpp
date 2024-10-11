// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "VarouGameModeBase.h"


AHorrorCharacter::AHorrorCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AHorrorCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	Stamina = MaxStamina;
    //Gun = GetWorld()->SpawnActor<AGun>(GunClass);
    //GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None); 
	//Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	//Gun->SetOwner(this);

	if (APlayerController* LocalPlayerController = Cast<APlayerController>(GetController()))
    {
        PlayerController = LocalPlayerController;
        if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(PlayerMapping, 0);
        }
    }	
}

void AHorrorCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D DirectionValue = Value.Get<FVector2D>();

	const FVector Forward = GetActorForwardVector();
    AddMovementInput(Forward, DirectionValue.Y);

	const FVector Right = GetActorRightVector();
    AddMovementInput(Right, DirectionValue.X);
}

void AHorrorCharacter::Run(const FInputActionValue& Value)
{
	bool IsRunKeyPressed = Value.Get<bool>();

	if (IsRunKeyPressed && Stamina > 0)
	{
		if (!IsRunning)
		{
			GetCharacterMovement()->MaxWalkSpeed = 600.0f;
			IsRunning = true; 
			
		}
	}
	else
		{
			GetCharacterMovement()->MaxWalkSpeed = 160.0f;
			IsRunning = false;
			
		}

		UE_LOG(LogTemp, Warning, TEXT("Stamina Left %f"),Stamina);

}

void AHorrorCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	} 
}

void AHorrorCharacter::Interaction(const FInputActionValue& Value)
{

}

// void AHorrorCharacter::Shoot()
// {
//     Gun->PullTrigger();
// }

// Called every frame

bool AHorrorCharacter::IsDead() const
{
    return Health <= 0;
    
}

float AHorrorCharacter::GetHealthPercent() const
{
    return Health / MaxHealth;
}

float AHorrorCharacter::GetStaminaPercent() const
{
    return Stamina / MaxStamina;
}
void AHorrorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsRunning)
    {
        if (Stamina > 0)
        {
            Stamina -= StaminaDrainRate * DeltaTime; 
            if (Stamina < 0)
            {
                Stamina = 0;
            }
        }
		else
        {
            GetCharacterMovement()->MaxWalkSpeed = 160.0f;
            IsRunning = false; 
        }

    }
    else
    {
        if (Stamina < MaxStamina)
        {
            Stamina += StaminaRecoverRate * DeltaTime; 
            if (Stamina > MaxStamina)
            {
                Stamina = MaxStamina;
            }
        }
    }
}


void AHorrorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered, this, &AHorrorCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered, this, &AHorrorCharacter::Look);
		EnhancedInputComponent->BindAction(RunAction,ETriggerEvent::Triggered, this, &AHorrorCharacter::Run);
        EnhancedInputComponent->BindAction(InteractionAction,ETriggerEvent::Triggered, this, &AHorrorCharacter::Interaction);
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Triggered, this, &ACharacter::Jump);

        //EnhancedInputComponent->BindAction(ShootAction,ETriggerEvent::Triggered, this, &AShooterCharacter::Shoot);
    }
}

// float AHorrorCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser)
// {
//     float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
//     DamageToApply = FMath::Min(Health, DamageToApply);
//     Health -= DamageToApply;

//     UE_LOG(LogTemp, Warning, TEXT("Health Left %f"),Health);

//     if (IsDead())
//     {
//         ATPSPROJECTGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ATPSPROJECTGameModeBase>();
//         if (GameMode != nullptr)
//         {
//             GameMode->PawnKilled(this);
//         }
//         DetachFromControllerPendingDestroy();
//         GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//     }

//     return DamageToApply;

//  }


