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
	FString ActorName = GetName();
	UE_LOG(LogTemp, Display, TEXT("Name: %s!"), *ActorName);
	UE_LOG(LogTemp, Display, TEXT("Test Message: %f!"), MoveDistance);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLoc = GetActorLocation();
	CurrentLoc += (PlatformVelocity * DeltaTime);
	SetActorLocation(CurrentLoc);
	
	if(ShouldPlatformReturn(CurrentLoc))
	{
		const FVector MoveDir = PlatformVelocity.GetSafeNormal();
		StartingPos = StartingPos + MoveDir * MoveDistance;
		SetActorLocation(StartingPos);
		PlatformVelocity = -PlatformVelocity;
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn(FVector CurrentLoc) const
{
	const float DistanceFromStartingPos = FVector::Dist(CurrentLoc, StartingPos);
	return DistanceFromStartingPos > MoveDistance;
}

 

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}


