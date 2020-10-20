
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
	if (PhysicsHandle){}
	else {
	
		UE_LOG(LogTemp, Error, TEXT("No physics handle found on %s"),
			*GetOwner()->FindComponentByClass<UGrabber>()->GetName());
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

FHitResult UGrabber::GetFirstPhysicsBodyInReach(FVector& PlayerViewPointLocation, FRotator& PlayerViewPointRotation, FVector& LineTraceEnd, FHitResult& ResultItem) const
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerViewPointLocation,
		OUT	PlayerViewPointRotation
	);
	
	//Debug Line
	/*DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0,255, 0),
		false,
		0.f,
		0,
		5.f
	);*/

	LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	FCollisionQueryParams TraceParams(FName(" "), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT ResultItem,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	if (ResultItem.GetActor()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ResultItem.GetActor()->GetName())
	}

	return ResultItem;
}



void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PhysicsHandle->GrabbedComponent) {
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT	PlayerViewPointLocation,
		OUT	PlayerViewPointRotation
		);

		LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LineTraceEnd.ToString());
	}
}


void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));

	FHitResult HitResult = GetFirstPhysicsBodyInReach(
		PlayerViewPointLocation,
		PlayerViewPointRotation,
		LineTraceEnd,
		ResultItem
	);
		ComponentToGrab = HitResult.GetComponent();
	if (HitResult.GetActor()) {
		PhysicsHandle->GrabComponentAtLocation
		(
			ComponentToGrab,
			NAME_None,
			LineTraceEnd
		);
	}

}

void UGrabber::Free() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));
	FHitResult HitResult = GetFirstPhysicsBodyInReach(
		PlayerViewPointLocation,
		PlayerViewPointRotation,
		LineTraceEnd,
		ResultItem
	);
	ComponentToGrab = HitResult.GetComponent();
	if (HitResult.GetActor()) {
		PhysicsHandle->ReleaseComponent();
	}
}