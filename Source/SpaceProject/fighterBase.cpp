// Fill out your copyright notice in the Description page of Project Settings.


#include "fighterBase.h"

AfighterBase::AfighterBase()
{

}

void AfighterBase::BeginPlay()
{
	Super::BeginPlay();
}

#if WITH_EDITOR
void AfighterBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangeEvent)
{
	Super::PostEditChangeProperty(PropertyChangeEvent);
	shipWeapons.WeaponOffsets.SetNum(shipWeapons.NumWeapons);
}
#endif

void AfighterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AfighterBase::FireWeapons()
{
	if (shipWeapons.GenAmmoCurrent > 0) {
		for (int i = 0; i < shipWeapons.WeaponOffsets.Num(); i++) {
			//spawn projectiles
		}
	}
	else {
		//no ammo cannot fire
	}
}

void AfighterBase::ReloadWeapons()
{
	if (shipWeapons.GenAmmoCurrent < shipWeapons.GenAmmoMax) {

	}
	else {
		//ammo full cannot reload
	}
}

void AfighterBase::FireTracking()
{
	if (shipWeapons.TrackAmmoCurrent > 0) {

	}
	else {
		//no tracking ammo cannot fire
	}
}

void AfighterBase::ReloadTracking()
{
	if (shipWeapons.TrackAmmoCurrent < shipWeapons.TrackAmmoMax) {

	}
	else {
		//tracking ammo full cannot reload
	}
}