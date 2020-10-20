// Copyright Michael Bridges 


#include "DoorOpen.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UDoorOpen::BeginPlay()
{

	Super::BeginPlay();

	InitYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitYaw;
	TargetYaw = InitYaw + 90.f;

	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
	 
	DoorLastOpend = 0.f;


}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	if (TriggerPlate && TriggerPlate->IsOverlappingActor(ActorThatOpen)) {
		OpenDoor(DeltaTime);
		DoorLastOpend = GetWorld()->GetTimeSeconds();
	}
	if (TriggerPlate && !TriggerPlate->IsOverlappingActor(ActorThatOpen))
	{
		if(GetWorld()->GetTimeSeconds() - DoorLastOpend >= DoorCloseDeltaSeconds)
		ClosingTheDoor(DeltaTime);
	}

	
	
}
 
void UDoorOpen::OpenDoor(const float& DeltaTime){

	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * DoorOpeningSpeed);
	DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}


void UDoorOpen::ClosingTheDoor(const float& DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitYaw , DeltaTime * DoorClosingSpeed);
	DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

}
