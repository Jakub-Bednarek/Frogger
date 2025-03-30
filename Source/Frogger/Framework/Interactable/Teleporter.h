// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

UCLASS()
class FROGGER_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	ATeleporter();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetTargetLevel(UWorld* Target);

	UFUNCTION(BlueprintCallable)
	void LoadTargetLevel();

protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<UWorld> TargetLevel = nullptr;
};
