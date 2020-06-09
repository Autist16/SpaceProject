//data structs for ship data and standard value updates
#pragma once
#include "GameFramework/FloatingPawnMovement.h"
#include "CoreMinimal.h"
#include "ShipDataStructs.generated.h"

////  ////  //// enum definiations  ////  ////  ////
UENUM(BlueprintType)
enum class EShipAlliance : uint8
{
	TEAM1 UMETA(DisplayName = "Team ONE"),
	TEAM2 UMETA(DisplayName = "Team TWO"),
	LONE UMETA(DisplayName = "Lone")
};

UENUM(BlueprintType)
enum class EShipType : uint8
{
	FIGHTER UMETA(DisplayName = "Fighter"),
	CARGO UMETA (DisplayName = "Cargo"),
	MOTHER UMETA (DisplayName = "Mother"),
	None
};

////  ////  ////  struct definiations  ////  ////  ////
//GENERAL INFORMATION
USTRUCT(BlueprintType)
struct FShipGeneral {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	EShipAlliance Alliance;
	UPROPERTY(EditDefaultsOnly)
	EShipType ShipType;
	UPROPERTY(EditDefaultsOnly)
	FString ModelName;

	FShipGeneral(EShipType type = EShipType::None) {
		Alliance = EShipAlliance::LONE;
		ShipType = type;
		ModelName = "";
	}
};

//FUEL INFORMATION
USTRUCT(BlueprintType)
struct FShipFuel {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int MaxFuel;
	UPROPERTY(EditAnywhere)
	int CurrentFuel;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float FuelLevel;

	FShipFuel(int Max = 100, int Current=100) {
		MaxFuel = Max;
		CurrentFuel = Current;
		FMath::Clamp(CurrentFuel, 0, MaxFuel);

		CalcLevel();
	}

	void CalcLevel() {
		FuelLevel = (CurrentFuel / MaxFuel);
	}
};

//HEALTH INFORMATION
USTRUCT(BlueprintType)
struct FShipHealth {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int MaxHealth;
	UPROPERTY(EditAnywhere)
	int CurrentHealth;
	UPROPERTY(VisibleAnywhere)
	float HealthLevel;
	
	FShipHealth(int Max = 100, int Current = 100) {
		MaxHealth = Max;
		CurrentHealth = Current;
		FMath::Clamp(CurrentHealth, 0, MaxHealth);

		CalcLevel();
	}

	void CalcLevel() {
		HealthLevel = CurrentHealth / MaxHealth;
	}
};

//MOVEMENT INFORMATION
USTRUCT(BlueprintType)
struct FShipMovement {
	GENERATED_BODY()
public:
	UFloatingPawnMovement* movementComponent;
	float acceleration;
	UPROPERTY(EditAnywhere)
	float TurnSpeed;
	UPROPERTY(EditAnywhere)
	float MaxSpeed;
	UPROPERTY(EditAnywhere)
	float currentSpeed;
	UPROPERTY(EditAnywhere)
	float rollCorrectionSpeed;

	FShipMovement(UFloatingPawnMovement *moveComp = nullptr, float maxSpeed=100.f){
		movementComponent = moveComp;
		acceleration = 0.0f;
		MaxSpeed = maxSpeed;
		currentSpeed = 0;
		rollCorrectionSpeed = 0.0f;
		TurnSpeed = 1.0f;
	}
};

//WEAPON INFORMATION
USTRUCT(BlueprintType)
struct FShipWeapons {
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		int NumWeapons;
	UPROPERTY(EditDefaultsOnly)
		TArray<FVector> WeaponOffsets;
	UPROPERTY()
		int GenAmmoMax;
	UPROPERTY()
		int GenAmmoCurrent;
	UPROPERTY()
		int TrackAmmoMax;
	UPROPERTY()
		int TrackAmmoCurrent;
	UPROPERTY(EditDefaultsOnly)
		float GenReloadTime;
	UPROPERTY(EditDefaultsOnly)
		float TrackReloadTime;

	FShipWeapons(int numWeapons = 1, int genMax =100, int trackingMax=10) {
		NumWeapons = numWeapons;
		WeaponOffsets.SetNum(NumWeapons);
		GenAmmoMax = genMax;
		TrackAmmoMax = trackingMax;

		GenAmmoCurrent = GenAmmoMax;
		TrackAmmoCurrent = TrackAmmoMax;
	}
	
	void GenReload() {
		GenAmmoCurrent = GenAmmoMax;
	}

	void TrackingReload() {
		TrackAmmoCurrent = TrackAmmoMax;
	}
};