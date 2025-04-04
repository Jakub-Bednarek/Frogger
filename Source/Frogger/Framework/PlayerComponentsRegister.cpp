// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PlayerComponentsRegister.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerComponentsRegister.h"

// Sets default values
APlayerComponentsRegister::APlayerComponentsRegister()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerComponentsRegister::BeginPlay()
{
	Super::BeginPlay();

	CreatePlayerComponents();
}

// Called every frame
void APlayerComponentsRegister::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerComponentsRegister::RegisterDefaultComponents(TArray<TSubclassOf<UActorComponent>> Components)
{
	DefaultComponents = MoveTemp(Components);
}

void APlayerComponentsRegister::RegisterLevelComponentsSet(TSoftObjectPtr<UWorld> Level, TArray<TSubclassOf<UActorComponent>> Components, bool CreateDefaults)
{
	FString LevelName = Level.GetAssetName();	
	LevelToComponentRegister.Emplace(MoveTemp(LevelName), LevelComponentsData { CreateDefaults, MoveTemp(Components) });

	UE_LOG(LogTemp, Verbose, TEXT("Successfully registered components set for level: %s"), (*LevelName));
}

void APlayerComponentsRegister::CreatePlayerComponents()
{
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	bool bCreateDefaults 	= false;
	auto* Player 			= UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto FoundComponentsSet = LevelToComponentRegister.Find(CurrentLevelName);

	if(FoundComponentsSet != nullptr)
	{
		for (const auto& Component : FoundComponentsSet->Components)
		{
			Player->AddComponentByClass(Component, false, FTransform {}, false);
		}
		
		bCreateDefaults = FoundComponentsSet->bCreateDefaults;
	}
	else
	{
		bCreateDefaults = true;

		UE_LOG(LogTemp, Verbose, TEXT("No player level specific components assigned to level: %s"), (*CurrentLevelName));
	}


	if (not bCreateDefaults)
	{
		return;
	}

	for (const auto& Component : DefaultComponents)
	{
		Player->AddComponentByClass(Component, false, FTransform {}, false);
	}

	UE_LOG(LogTemp, Verbose, TEXT("All player components created for level: %s"), (*CurrentLevelName));
}
