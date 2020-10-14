// Copyright Michael Bridges 2019


#include "DoorOpen.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();
	FRotator Current_rotation = GetOwner()->GetActorRotation();
	FRotator Modifing_rotation = Current_rotation + FRotator(0.f, 90.f, 0.f);
	GetOwner()->SetActorRotation(Modifing_rotation);
	// ...
	
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is equal: %f"), GetOwner()->GetActorRotation().Yaw);
	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator OpenDoor(0.f, TargetYaw, 0.f);
	OpenDoor.Yaw =  FMath::Lerp(CurrentYaw,TargetYaw,0.2f);
	GetOwner()->SetActorRotation(OpenDoor);
}
 
