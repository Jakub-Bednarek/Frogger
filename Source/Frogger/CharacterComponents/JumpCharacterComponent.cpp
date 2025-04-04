// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponents/JumpCharacterComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "JumpCharacterComponent.h"

UJumpCharacterComponent::UJumpCharacterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UJumpCharacterComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterOwner = Cast<ACharacter>(GetOwner());
	check(CharacterOwner != nullptr);

	BindInputActions();
}


void UJumpCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UJumpCharacterComponent::OnJumpPressed()
{
	UE_LOG(LogTemp, Error, TEXT("START JUMP"));
	if (CharacterOwner->GetVelocity().Size() <= 0)
	{
		bIsJumpingInPlace = true;
	}
	else
	{
		bIsJumpingInPlace = false;
	}

	JumpHoldTime = 0.0f;
	// GetWorldTimerManager().SetTimer(JumpTimerHandle, this, &UJumpCharacterComponent::UpdateJumpTimer, 0.01f, true);
}

void UJumpCharacterComponent::OnJumpReleased()
{
	UE_LOG(LogTemp, Error, TEXT("END JUMP"));
	// GetWorldTimerManager().ClearTimer(JumpTimerHandle);
	auto* OwnerMovementComponent = CharacterOwner->GetCharacterMovement(); 
	if (OwnerMovementComponent->IsFalling())
	{
		return;
	}
	
	const float JumpStrength = FMath::Lerp(MinJumpStrength, MaxJumpStrength, JumpHoldTime / MaxJumpHoldTime);
	OwnerMovementComponent->JumpZVelocity = JumpStrength;
	if (CharacterOwner->GetVelocity().Size() <= 0)
	{
		CharacterOwner->Jump();
	}
	else
	{
		FVector ForwardVelocity = CharacterOwner->GetActorForwardVector() * JumpStrength;
		FVector UpwardVelocity = FVector(0, 0, JumpStrength * 0.6f);
		
		// LaunchCharacter(ForwardVelocity + UpwardVelocity, true, true);
	}

	// bIsJumpingInPlace = false;
}

void UJumpCharacterComponent::UpdateJumpTimer()
{
	if (JumpHoldTime < 2)
	{
		JumpHoldTime += 0.01f;
		bIsMaxJumpPower = false;
	}
	else if (!bIsMaxJumpPower)
	{
		// OnJumpHoldMaxReached();
		bIsMaxJumpPower = true;
		// GetWorldTimerManager().ClearTimer(JumpTimerHandle);
	}
}

void UJumpCharacterComponent::BindInputActions()
{
	auto Owner = GetOwner();
	auto PlayerInputComponent = Owner->InputComponent;
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &UJumpCharacterComponent::OnJumpPressed);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &UJumpCharacterComponent::OnJumpReleased);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}