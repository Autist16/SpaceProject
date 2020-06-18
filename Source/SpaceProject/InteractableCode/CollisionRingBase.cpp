// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionRingBase.h"

// Sets default values
ACollisionRingBase::ACollisionRingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ringRadius = 50.0f;
	numEmitters = 4;
	segments = 6;
	ringPath = CreateDefaultSubobject<USplineComponent>(TEXT("ring path"));
	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("collider"));

	RootComponent = ringPath;
	pathType = ESplinePointType::Constant;

	SetupSpline();
	SetupEmitters();

	collider->AttachToComponent(ringPath, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ACollisionRingBase::BeginPlay()
{
	Super::BeginPlay();
	splineLength = ringPath->GetSplineLength();
}

#if WITH_EDITOR
void ACollisionRingBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	SetupSpline();

	float size = ringRadius*0.75;
	collider->SetBoxExtent(FVector(10, size, size));
}
#endif

// Called every frame
void ACollisionRingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveEmitters();
}
void ACollisionRingBase::MoveEmitters()
{
	emitterDistance += speed;
	if (emitterDistance >= splineLength) {
		emitterDistance -= splineLength;
	}

	emitter->SetRelativeTransform(ringPath->GetTransformAtDistanceAlongSpline(emitterDistance, ESplineCoordinateSpace::Local));
}

void ACollisionRingBase::SetupSpline()
{
	TArray<FVector> pointLocations;
	float angle = FMath::DegreesToRadians(360) / segments;
	float a, b;
	for (int i = 0; i < segments; i++) {
		a = ringRadius * cos(angle*i);
		b = ringRadius * sin(angle * i);

		pointLocations.Add(FVector(0, a, b));
	}

	ringPath->ClearSplinePoints();

	for (int i = 0; i < pointLocations.Num(); i++) {
		ringPath->AddSplineLocalPoint(pointLocations[i]);
	}

	for (int j = 0; j < ringPath->GetNumberOfSplinePoints(); j++) {
		ringPath->SetSplinePointType(j, pathType, true);
	}

	//close loop
	ringPath->SetClosedLoop(true, true);
	
}

void ACollisionRingBase::SetupEmitters()
{
	emitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("emitter"));
	emitterDistance = 0;
	emitter->AttachToComponent(ringPath, FAttachmentTransformRules::KeepRelativeTransform);
	emitter->SetRelativeTransform(ringPath->GetTransformAtDistanceAlongSpline(emitterDistance, ESplineCoordinateSpace::Local));
}