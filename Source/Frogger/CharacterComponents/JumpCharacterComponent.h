// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "JumpCharacterComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJumpEvent, const float, JumpStrength);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class FROGGER_API UJumpCharacterComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UJumpCharacterComponent();

    UFUNCTION(BlueprintCallable)
    void SetMaxJumpHoldTime(const float Value);

    UFUNCTION(BlueprintCallable)
    void SetMinJumpStrength(const float Value);

    UFUNCTION(BlueprintCallable)
    void SetMaxJumpStrength(const float Value);

    UFUNCTION(BlueprintCallable)
    float GetMaxJumpHoldTime();

    UFUNCTION(BlueprintCallable)
    float GetMinJumpStrength();

    UFUNCTION(BlueprintCallable)
    float GetMaxJumpStrength();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction *ThisTickFunction) override;

public:
    /** Jump Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction *JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FOnJumpEvent OnJumpEvent;

protected:
    virtual void BeginPlay() override;

    virtual void OnJumpPressed();
    virtual void FireJumpEvent();

private:
    void BindInputActions();

private:
    inline static constexpr float DefaultMaxJumpHoldTime = 1.0f;
    inline static constexpr float DefaultMinJumpStrength = 700.0f;
    inline static constexpr float DefaultMaxJumpStrength = 1200.0f;

    FTimerHandle JumpTimerHandle;

    float MaxJumpHoldTime;
    float MinJumpStrength;
    float MaxJumpStrength;

    ACharacter *CharacterOwner;
};
