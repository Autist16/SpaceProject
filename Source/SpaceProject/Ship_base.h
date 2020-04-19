// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
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

	//visual components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship Model")
		UFloatingPawnMovement* movementComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ship Model")
		UStaticMesh* shipMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Model")
		UStaticMeshComponent* ship;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Model")
		TArray<UMaterialInterface*> shipMaterials;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ship Model")
		USpringArmComponent* cameraArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ship Model")
		UCameraComponent* shipCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ship Model")
		FTransform cameraTransform;

protected:
	void MoveShip();
	UFUNCTION(BlueprintCallable, Category = "Ship Movement")
		void TurnShip(float controlAxisVal);
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Movement")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Temp")
		float rollSpeed;

private:
	void SetCameraRotation();
	FRotator cameraRot;
};
