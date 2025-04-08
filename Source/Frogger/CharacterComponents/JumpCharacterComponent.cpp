// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponents/JumpCharacterComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"
#include "TimerManager.h"
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

	SetMaxJumpHoldTime(DefaultMaxJumpHoldTime);
	SetMinJumpStrength(DefaultMinJumpStrength);
	SetMaxJumpStrength(DefaultMaxJumpStrength);
}


void UJumpCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UJumpCharacterComponent::SetMaxJumpHoldTime(const float Value)
{
	if (Value < 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to set MaxJumpHoldTime, value must be greater than 0. Defaulting to %f"), DefaultMaxJumpHoldTime);

		MaxJumpHoldTime = DefaultMaxJumpHoldTime;

		return;
	}

	MaxJumpHoldTime = Value;
}

// TODO: check for Min > Max?
void UJumpCharacterComponent::SetMinJumpStrength(const float Value)
{
	if (Value < 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to set MinJumpStrength, value must be greater or equal 0. Defaulting to %f"), DefaultMinJumpStrength);

		MinJumpStrength = DefaultMinJumpStrength;

		return;
	}

	MinJumpStrength = Value;
}

// TODO: check for Max > Min?
void UJumpCharacterComponent::SetMaxJumpStrength(const float Value)
{
	if (Value < 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to set MaxJumpStrength, value must be greater or equal 0. Defaulting to %f"), DefaultMaxJumpStrength);

		MaxJumpStrength = DefaultMaxJumpStrength;

		return;
	}

	MaxJumpStrength = Value;
}

float UJumpCharacterComponent::GetMaxJumpHoldTime()
{
	return MaxJumpHoldTime;
}

float UJumpCharacterComponent::GetMinJumpStrength()
{
	return MinJumpStrength;
}

float UJumpCharacterComponent::GetMaxJumpStrength()
{
	return MaxJumpStrength;
}

void UJumpCharacterComponent::OnJumpPressed()
{
	GetWorld()->GetTimerManager().SetTimer(JumpTimerHandle, this, &UJumpCharacterComponent::FireJumpEvent, MaxJumpHoldTime, false);
}

void UJumpCharacterComponent::FireJumpEvent()
{
	auto& TimerManager = GetWorld()->GetTimerManager();
	const float TimeElapsed = TimerManager.GetTimerElapsed(JumpTimerHandle);
	const float JumpStrength = FMath::Lerp(MinJumpStrength, MaxJumpStrength, TimeElapsed / MaxJumpHoldTime);

	if (OnJumpEvent.IsBound())
	{
		OnJumpEvent.Broadcast(JumpStrength);
	}

	TimerManager.ClearTimer(JumpTimerHandle);
}

void UJumpCharacterComponent::BindInputActions()
{
	auto Owner = GetOwner();
	auto PlayerInputComponent = Owner->InputComponent;
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &UJumpCharacterComponent::OnJumpPressed);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &UJumpCharacterComponent::FireJumpEvent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}