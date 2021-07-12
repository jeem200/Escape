// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void GrabObject();

	void ReleaseObject();

	void SetUpInputComponent();

	void FindHandle();

	FHitResult GetPhysicsBody() const;

	FVector GetLineTraceEnd() const;

	FVector GetPlayerWorldPosition() const;
	FVector GetPlayerWorldRotation() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	float Reach=300.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;


};
