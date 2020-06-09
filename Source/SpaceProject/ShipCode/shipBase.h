// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ShipDataStructs.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "shipBase.generated.h"

UCLASS()
class SPACEPROJECT_API AshipBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AshipBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//Ship
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Data")
		FShipGeneral shipGeneralData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Data")
		FShipFuel shipFuel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Data")
		FShipHealth shipHealth;

protected:
	//Ship model variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ship Model")
		UStaticMesh* shipMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Model")
		UStaticMeshComponent* ship;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ship Model")
		TArray<UMaterialInterface*> shipMaterials;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ship Model")
		USpringArmComponent* cameraArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ship Model")
		UCameraComponent* shipCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ship Model")
		FTransform cameraTransform;

	//ship movement variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Movement")
		FShipMovement shipMovement;

	//BLUEPRINT CALLABLE FUNCTIONS
	UFUNCTION(BlueprintCallable, Category = "Ship Movement")
		void Accelerate(float triggerVal);

	UFUNCTION(BlueprintCallable, Category = "Ship Movement")
		void TurnShip(float controlAxisVal);
	UFUNCTION(BlueprintCallable, Category = "Ship Movement")
		void PitchShip(float controlAxisVal);
	UFUNCTION(BlueprintCallable, Category = "Ship Movement")
		void RollShip(float controlAxisVal);

private:
	FRotator cameraRot;
	float levelRoll;

	void MoveShip();
	void SetCameraRotation();
};
