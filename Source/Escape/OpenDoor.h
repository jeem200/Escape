// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Components/AudioComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float GetTotalMass();
	void FindAudioComponent() ;
private:

	

	UPROPERTY(EditAnywhere)
	float InitialYaw;
	UPROPERTY(EditAnywhere)
	float CurrentYaw;
	UPROPERTY(EditAnywhere)
	float TargetYaw=90.f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* DoorTrigger;

	float DoorLastOpen=0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 2.f;
	
	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 2.f;


	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50.f;

	UPROPERTY(EditAnywhere)
	UAudioComponent* DoorSound=nullptr ;

	bool CloseDoorSound = true;
	bool OpenDoorSound = false;
	
};
