// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Interactable/Teleporter.h"

#include <Kismet/GameplayStatics.h>

// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleporter::SetTargetLevel(UWorld* Target)
{
	if (Target == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Provided Target in SetTargetLevel() is null."));
		return;
	}

	TargetLevel = Target;
}

void ATeleporter::LoadTargetLevel()
{
	const auto LevelName = TargetLevel->GetMapName();

	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
}