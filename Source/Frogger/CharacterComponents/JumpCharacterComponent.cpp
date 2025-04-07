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
}


void UJumpCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UJumpCharacterComponent::OnJumpPressed()
{
	GetWorld()->GetTimerManager().SetTimer(JumpTimerHandle, this, &UJumpCharacterComponent::FireJumpEvent, MaxJumpHoldTime, false);
}

void UJumpCharacterComponent::FireJumpEvent()
{
	auto& TimerManager = GetWorld()->GetTimerManager();
	const auto TimeElapsed = TimerManager.GetTimerElapsed(JumpTimerHandle);
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