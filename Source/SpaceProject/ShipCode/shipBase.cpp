// Fill out your copyright notice in the Description page of Project Settings.


#include "shipBase.h"

// Sets default values
AshipBase::AshipBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("AnchorPoint"));

	ship = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship_Main"));
	cameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera_Arm"));
	shipCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Ship_Camera"));

	UFloatingPawnMovement *temp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("movementCompoent"));
	shipMovement = FShipMovement(temp, 200.0f);

	//attach components
	ship->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	cameraArm->AttachToComponent(ship, FAttachmentTransformRules::KeepRelativeTransform);
	shipCamera->AttachToComponent(cameraArm, FAttachmentTransformRules::KeepRelativeTransform);

	levelRoll = 0.0f;
}

// Called when the game starts or when spawned
void AshipBase::BeginPlay()
{
	Super::BeginPlay();
}

#if WITH_EDITOR
void AshipBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (shipMesh) {
		ship->SetStaticMesh(shipMesh);
		shipMaterials.SetNum(shipMesh->StaticMaterials.Num());

		for (int i = 0; i < shipMaterials.Num(); i++) {
			if (shipMaterials[i]) {
				shipMesh->SetMaterial(i, shipMaterials[i]);
			}
			else {
				shipMaterials[i] = shipMesh->StaticMaterials[i].MaterialInterface;
			}
		}

	}

	shipCamera->SetRelativeTransform(cameraTransform);
}
#endif

// Called every frame
void AshipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AshipBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AshipBase::Accelerate(float triggerVal)
{
	if (triggerVal == 0.0f) {
		//slowly decelerate
		shipMovement.currentSpeed = -2.0f;
	}
	else if (triggerVal > 0.75) {
		//accerlerate
		shipMovement.currentSpeed += triggerVal * shipMovement.acceleration;
	}
	//else maintain current speed

	//clamp speed limits
	FMath::Clamp(shipMovement.currentSpeed, 0.0f, shipMovement.MaxSpeed);

}

void AshipBase::TurnShip(float controlAxisVal)
{
	/*need to consider adding a turn speed to this
	(eg fighters and more agile than a cargo ship)
	but the turning process should be the same just more/less responsive*/
	float roll = ship->GetRelativeRotation().Roll;
	if (controlAxisVal != 0.0f) {
		//clamp roll to avoid over spinning
		if (roll >= -75 && roll <= 75) {
			ship->AddRelativeRotation(FRotator(0.0f, controlAxisVal, controlAxisVal / 6));
		}
		else {
			ship->AddRelativeRotation(FRotator(0.0f, controlAxisVal, 0));
		}
	}
	else {
		//return to level flight
		if (roll != levelRoll) {
			float changeVal = (abs(roll) + 25) / 75; //generic example needs more work
			//clamp to zero when needed to avoid flickering at near values
			if (roll < shipMovement.rollCorrectionSpeed && roll > -shipMovement.rollCorrectionSpeed) {
				ship->SetRelativeRotation(FRotator(0.0f, 0.0f, levelRoll));
			}
			else if (roll <= -1) {
				ship->AddRelativeRotation(FRotator(0.0f, 0.0f, shipMovement.rollCorrectionSpeed * changeVal));
			}
			else {
				ship->AddRelativeRotation(FRotator(0.0f, 0.0f, -shipMovement.rollCorrectionSpeed * changeVal));
			}
		}
	}

	SetCameraRotation();
}

void AshipBase::PitchShip(float controlAxisVal) {
	//add a turn speed adjustment
	ship->AddLocalRotation(FRotator(controlAxisVal, 0.0f, 0.0f));

}
void AshipBase::RollShip(float controlAxisVal) {
	//add a turn speed adjustment
	ship->AddLocalRotation(FRotator(0.0f, 0.0f, controlAxisVal));
	levelRoll = ship->GetRelativeRotation().Roll;
}

void AshipBase::MoveShip()
{
	shipMovement.movementComponent->Velocity = (ship->GetForwardVector() * shipMovement.currentSpeed);
}

void AshipBase::SetCameraRotation() {
	cameraRot.Roll = ship->GetRelativeRotation().Roll * (-1.0);
	shipCamera->SetRelativeRotation(cameraRot);
}