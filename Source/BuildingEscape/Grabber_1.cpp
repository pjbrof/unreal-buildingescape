// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber_1.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber_1::UGrabber_1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber_1::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{
		// Physics Handle Found
		UE_LOG(LogTemp, Warning, TEXT("%s now has a physics handle component."), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component."), *GetOwner()->GetName());
	}


	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		// Physics Handle Found
		UE_LOG(LogTemp, Warning, TEXT("%s now has a input handle component."), *GetOwner()->GetName());

		// Bind the input action
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber_1::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber_1::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input handle component."), *GetOwner()->GetName());
	}
}

void UGrabber_1::Grab() 
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed!"));
}

void UGrabber_1::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released!"));
}


// Called every frame
void UGrabber_1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255,0,0),
		false,
		0.f,
		0.f,
		10.f
	);

	// UE_LOG(LogTemp, Warning, TEXT("Location: %s Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	// Line Trace - RayCasting
	FHitResult Hit;

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit %s"), *(ActorHit->GetName()));
	}
}