// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "PlayerComponentsRegister.generated.h"

struct LevelComponentsData
{
	bool bCreateDefaults;
	TArray<TSubclassOf<UActorComponent>> Components;
};

UCLASS()
class FROGGER_API APlayerComponentsRegister : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerComponentsRegister();
	
	UFUNCTION(BlueprintCallable)
	void RegisterDefaultComponents(TArray<TSubclassOf<UActorComponent>> Components);

	UFUNCTION(BlueprintCallable)
	void RegisterLevelComponentsSet(TSoftObjectPtr<UWorld> Level, TArray<TSubclassOf<UActorComponent>> Components, bool CreateDefaults = true);

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	void CreatePlayerComponents();

private:
	TArray<TSubclassOf<UActorComponent>> DefaultComponents {};
	TMap<FString, LevelComponentsData> 	 LevelToComponentRegister {};
};
