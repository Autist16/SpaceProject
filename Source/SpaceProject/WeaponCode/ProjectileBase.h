// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class SPACEPROJECT_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
#endif

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
		UProjectileMovementComponent* movementComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Settings")
		USphereComponent* sphereCollider;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Settings")
		UParticleSystemComponent* particalSystem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Settings")
		float colliderSize;

};
