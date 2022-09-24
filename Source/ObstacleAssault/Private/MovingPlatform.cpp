// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartingPos = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLoc = GetActorLocation();
	CurrentLoc += (Velocity * DeltaTime);
	SetActorLocation(CurrentLoc);
	const float DistanceFromStartingPos = FVector::Dist(CurrentLoc, StartingPos);
	if(DistanceFromStartingPos > MoveDistance)
	{
		const FVector MoveDir = Velocity.GetSafeNormal();
		StartingPos = StartingPos + MoveDir * MoveDistance;
		SetActorLocation(StartingPos);
		Velocity = -Velocity;
	}
}

