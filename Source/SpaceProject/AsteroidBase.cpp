// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidBase.h"

// Sets default values
AAsteroidBase::AAsteroidBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//initalise objects
	asteroidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Asteroid");
	RootComponent = asteroidMeshComponent;
	meshScale = 1.0;
}

// Called when the game starts or when spawned
void AAsteroidBase::BeginPlay()
{
	Super::BeginPlay();

}

#if WITH_EDITOR
void AAsteroidBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//set the asteroid size
	asteroidMeshComponent->RelativeScale3D = FVector(1.f, 1.f, 1.f) * meshScale;
	
	//set the random mesh choice
	if (meshChoices.Num() > 0) {
		asteroidMeshComponent->SetStaticMesh(GetRandomMesh());
	}
}
#endif

// Called every frame
void AAsteroidBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RootComponent->AddRelativeRotation(spinVal);
}

UStaticMesh* AAsteroidBase::GetRandomMesh()
{
	int maxIdx = meshChoices.Num();
	int idx;
	UStaticMesh* selected = nullptr;

	while (selected != nullptr) {
		idx = rand() % maxIdx;
		selected = meshChoices[idx];
	}

	return selected;
}
