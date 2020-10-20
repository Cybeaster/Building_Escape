
#include "Grabber.h"

#define OUT

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();

}

void UGrabber::FindPhysicsHandle() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr){
		UE_LOG(LogTemp, Error, TEXT("Physics Handle component haven't been found"));
	}
	
}

void UGrabber::SetupInputComponent() {

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Error, TEXT("Movement component found on %s"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Free);
	}
	else{
		UE_LOG(LogTemp, Error, TEXT("No input component found on %s"),
			*GetOwner()->FindComponentByClass<UGrabber>()->GetName());
	}
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach(FHitResult& ResultItem) const
{

	FCollisionQueryParams TraceParams(FName(" "), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT ResultItem,
		GetPlayerPosition(),
		GetPlayerReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	return ResultItem;
}



void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}
}


void UGrabber::Grab() {
	FHitResult HitResult = GetFirstPhysicsBodyInReach(ResultItem);
		ComponentToGrab = HitResult.GetComponent();
	if (HitResult.GetActor()) {
		PhysicsHandle->GrabComponentAtLocation
		(
			ComponentToGrab,
			NAME_None,
			GetPlayerReach()
		);
	}

}
void UGrabber::Free() {
		PhysicsHandle->ReleaseComponent();
}


FVector UGrabber::GetPlayerReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerViewPointLocation,
		OUT	PlayerViewPointRotation
	);

	return (PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach);
	
}
FVector UGrabber::GetPlayerPosition()const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerViewPointLocation,
		OUT	PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}