// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidBase.generated.h"

UCLASS()
class SPACEPROJECT_API AAsteroidBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid Visuals")
		UStaticMeshComponent* asteroidMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid Visuals")
		TArray<UStaticMesh*> meshChoices;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asteroid Visuals")
		float meshScale;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asteroid Visuals")
		FRotator spinVal;

private:
	UStaticMesh* GetRandomMesh();
};
