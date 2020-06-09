// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShipCode/shipBase.h"
#include "fighterBase.generated.h"

/**
 * 
 */
UCLASS()
class SPACEPROJECT_API AfighterBase : public AshipBase
{
	GENERATED_BODY()
	
public:
	AfighterBase();

protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Data")
		FShipWeapons shipWeapons;

protected:
	UFUNCTION(BlueprintCallable, Category = "Figher Ship")
		void FireWeapons();
	UFUNCTION(BlueprintCallable, Category = "Figher Ship")
		void ReloadWeapons();
	UFUNCTION(BlueprintCallable, Category = "Fighter Ship")
		void FireTracking();
	UFUNCTION(BlueprintCallable, Category = "Fighter Ship")
		void ReloadTracking();


};
