// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "JumpCharacterComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJumpEvent, const bool, bIsMaxHeight);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class FROGGER_API UJumpCharacterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UJumpCharacterComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

protected:
	virtual void BeginPlay() override;

private:
	void OnJumpPressed();
	void OnJumpReleased();

	void UpdateJumpTimer();

	void BindInputActions();

private:
	FTimerHandle JumpTimerHandle;

	bool bIsJumpingInPlace;
	bool bIsMaxJumpPower;
	
	float JumpHoldTime = 0.0f;
	float MaxJumpHoldTime = 1.0f; // Maximum time jump can be charged
	float MinJumpStrength = 700.f; // Minimum jump force
	float MaxJumpStrength = 1200.f; // Maximum jump force

	ACharacter* CharacterOwner;
};
