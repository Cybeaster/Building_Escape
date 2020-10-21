// Copyright Michael Bridges 


#include "DoorOpen.h"
#include "GameFramework/Actor.h"

#define OUT
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

	DoorLastOpend = 0.f;

	FindAudioComponent();
	FindPressurePlate();


}


void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	if (TotalMassOfActors() > MassMakeDoorOpen) {
		
		OpenDoor(DeltaTime);
		DoorLastOpend = GetWorld()->GetTimeSeconds();
	}

	if (TotalMassOfActors() < MassMakeDoorOpen)
	{
		if(GetWorld()->GetTimeSeconds() - DoorLastOpend >= DoorCloseDeltaSeconds)
		ClosingTheDoor(DeltaTime);
	}

	
	
}
 
void UDoorOpen::OpenDoor(const float& DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * DoorOpeningSpeed);
	DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	CloseDoorSound = false;
	if (!DoorSound) {
		UE_LOG(LogTemp, Error, TEXT("%s couldn't be found!"), *DoorSound->GetName());
		return;
	}
	if (!OpenDoorSound) {
		DoorSound->Play();
		OpenDoorSound = true;
	}
}


void UDoorOpen::ClosingTheDoor(const float& DeltaTime)
{

	CurrentYaw = FMath::Lerp(CurrentYaw, InitYaw , DeltaTime * DoorClosingSpeed);
	DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	OpenDoorSound = false;
	if (!DoorSound) {
		UE_LOG(LogTemp, Error, TEXT("%s couldn't be found!"), *DoorSound->GetName());
		return;
	}
	if (!CloseDoorSound) {
		DoorSound->Play();
		CloseDoorSound = true;
	}
	
}

float UDoorOpen::TotalMassOfActors() const 
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	if (!TriggerPlate)
	{
		UE_LOG(LogTemp, Error, TEXT("!Physicshandle couldn't be found!"))
			return TotalMass;
	}
	TriggerPlate->GetOverlappingActors(OUT OverlappingActors);

	for (auto T : OverlappingActors) {
		TotalMass+=	T->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

void UDoorOpen::FindAudioComponent() {
	DoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!DoorSound)
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't be found %s component"), *DoorSound->GetName());
	}
}

void UDoorOpen::FindPressurePlate() const
{
	if (!TriggerPlate) {
		UE_LOG(LogTemp, Warning, TEXT("%s Couldn't be found"), *TriggerPlate->GetName());
	}
}
