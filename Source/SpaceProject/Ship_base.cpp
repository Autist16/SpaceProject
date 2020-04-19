// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship_base.h"

// Sets default values
AShip_base::AShip_base()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Anchor");
	movementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	ship = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("shipMain"));
	cameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("camera Arm"));
	shipCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("shipCamera"));

	ship->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	cameraArm->AttachToComponent(ship, FAttachmentTransformRules::KeepRelativeTransform);
	shipCamera->AttachToComponent(cameraArm, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AShip_base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShip_base::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangeEvent)
{
	Super::PostEditChangeProperty(PropertyChangeEvent);
	
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
// Called every frame
void AShip_base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveShip();
}

// Called to bind functionality to input
void AShip_base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AShip_base::MoveShip()
{
	movementComponent->Velocity = (ship->GetForwardVector() * Speed);
}
void AShip_base::TurnShip(float controlAxisVal)
{
	float roll = ship->GetRelativeRotation().Roll;
	if (controlAxisVal != 0.0f) {
		//clamp roll
		if (roll >= -75 && roll < 75) {
			ship->AddRelativeRotation(FRotator(0.0, controlAxisVal, (controlAxisVal / 6)));
		}
		else {
			ship->AddRelativeRotation(FRotator(0.0f, controlAxisVal, 0));
		}
	}
	else {
		//return ship to level flight
		if (roll != 0) {
			float changeVal = (abs(roll)+25) / 75;
			//clamp to zero
			if (roll < rollSpeed && roll > -rollSpeed) {
				ship->AddRelativeRotation(FRotator(0.0, 0.0, -roll));
			}
			else if (roll <=-1) {
				ship->AddRelativeRotation(FRotator(0.0f, 0.0f, rollSpeed*changeVal));
			}
			else {
				ship->AddRelativeRotation(FRotator(0.0f, 0.0f, -rollSpeed*changeVal));
			}
		}
	}
	SetCameraRotation();
}

void AShip_base::SetCameraRotation()
{
	cameraRot.Roll = ship->GetRelativeRotation().Roll*-1.0;
	shipCamera->SetRelativeRotation(cameraRot);
}