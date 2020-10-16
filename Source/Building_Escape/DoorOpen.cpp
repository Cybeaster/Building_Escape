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
	/*CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw,DeltaTime, 2.f);
	GetOwner()->SetActorRotation(OpenDoor);*/
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
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * 1.f);
	DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
}

void UDoorOpen::ClosingTheDoor(const float& DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitYaw , DeltaTime * 1.f);
	DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

}
