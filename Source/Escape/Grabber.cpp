// Fill out your copyright notice in the Description page of Project Settings.



#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"


#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindHandle();
	SetUpInputComponent();
	


	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	DrawDebugLine(
		GetWorld(),
		GetPlayerWorldPosition(),
		GetLineTraceEnd(),
		FColor(0, 255, 0),
		false,
		0.f,
		0.5f,
		5.f
	);
	
	if(PhysicsHandle->GrabbedComponent)
	{
		
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
	


}

void UGrabber::GrabObject() 
{
	//UE_LOG(LogTemp, Error, TEXT("Grab Pressed"));
	FHitResult HitResult = GetPhysicsBody();
	
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	if (HitResult.GetActor()) 
	{
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, GetLineTraceEnd());
	}
	
}

void UGrabber::ReleaseObject()
{
	//UE_LOG(LogTemp, Error, TEXT("Grab Released"));

	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindHandle() 
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle==nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PHYSICS HANDLE COMPONENT FOUND"));
	}
	
}


void UGrabber::SetUpInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabObject);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseObject);
	}

}


FHitResult UGrabber::GetPhysicsBody() const
{
	

	

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());


	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerWorldPosition(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Error, TEXT("ACTOR IS %S"), *(ActorHit)->GetName());
	
		
	}

	return Hit;
}

FVector UGrabber::GetLineTraceEnd() const
{
	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);


	return GetPlayerWorldPosition() + PlayerViewPointRotation.Vector() * Reach;
}

FVector UGrabber::GetPlayerWorldPosition() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);


	return GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
}


