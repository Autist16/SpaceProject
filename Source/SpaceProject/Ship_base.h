// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ship_base.generated.h"

UCLASS()
class SPACEPROJECT_API AShip_base : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip_base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangeEvent) override;
#endif 


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RollShip(int direction);

	//visual components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ship Model")
		UStaticMesh* shipMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Model")
		UStaticMeshComponent* ship;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Model")
		TArray<UMaterialInterface*> shipMaterials;

private:


};
