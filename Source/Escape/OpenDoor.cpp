// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//PrimaryComponentTick.bStartWithTickEnabled = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	//

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;
	DoorTrigger = GetWorld()->GetFirstPlayerController()->GetPawn();
	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Actor Not Set"), *GetOwner()->GetName());
	}

	FindAudioComponent();
	 
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	/*UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);*/

	if(PressurePlate && GetTotalMass()> MassToOpenDoor)
	{
		
		OpenDoor(DeltaTime);
		DoorLastOpen = GetWorld()->GetTimeSeconds();
	}
	else 
	{
		if ((GetWorld()->GetTimeSeconds()- DoorLastOpen)>DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
		
	}
	
	// ...
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	CloseDoorSound = false;

	if (!OpenDoorSound)
	{
		DoorSound->Play();
		OpenDoorSound = true;
	}

}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	OpenDoorSound = false;
	if (!CloseDoorSound)
	{
		DoorSound->Play();
		CloseDoorSound = true;
	}


}
float UOpenDoor:: GetTotalMass()
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActor;

	PressurePlate->GetOverlappingActors(OverlappingActor);

	for (AActor* Actor : OverlappingActor) 
	{	
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

void UOpenDoor::FindAudioComponent() 
{
	DoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!DoorSound) 
	{
		UE_LOG(LogTemp, Error, TEXT("No Audio"));
	}
}
