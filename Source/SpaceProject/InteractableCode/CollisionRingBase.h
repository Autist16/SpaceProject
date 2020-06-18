// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollisionRingBase.generated.h"

UCLASS()
class SPACEPROJECT_API ACollisionRingBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollisionRingBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChainedEvent) override;
#endif 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Ring Settings")
		float ringRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Ring Settings")
		USplineComponent* ringPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Ring Settings")
		UBoxComponent* collider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Ring Settings")
		TEnumAsByte<ESplinePointType::Type> pathType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Ring Visuals")
		UParticleSystemComponent* emitter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Ring Settings")
		int segments;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Ring Settings")
		float speed;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnRingCollision"), Category = "Collision Task")
		void OnRingCollisionEvent();

private:
	int numEmitters;
	float emitterDistance;
	float splineLength;

	void MoveEmitters();

	void SetupSpline();
	void SetupEmitters();
};
