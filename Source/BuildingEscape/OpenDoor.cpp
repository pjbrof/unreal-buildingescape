// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	AActor* Owner = GetOwner();

	FRotator NewRotation = FRotator(0.f, 120.f, 0.f);

	Owner->SetActorRotation(NewRotation);

	UE_LOG(LogTemp, Warning, TEXT("We opened the door"));
}

void UOpenDoor::CloseDoor()
{
	AActor* Owner = GetOwner();

	FRotator NewRotation = FRotator(0.f, 0.f, 0.f);

	Owner->SetActorRotation(NewRotation);

	UE_LOG(LogTemp, Warning, TEXT("We closed the door"));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	}
	else {
		CloseDoor();
	}

	
}

