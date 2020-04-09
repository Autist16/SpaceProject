// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship_base.h"

// Sets default values
AShip_base::AShip_base()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ship = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("shipMain"));
	RootComponent = ship;
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
}
// Called every frame
void AShip_base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShip_base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AShip_base::RollShip(int direction)
{

}

