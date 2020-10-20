// Copyright Michael Bridges 2019

#pragma once
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction) override;
	
	void Grab();
	void Free();

	void FindPhysicsHandle();
	void SetupInputComponent();
	
	FVector GetPlayerPosition() const;
	FVector GetPlayerReach() const;


private:
	
	UPrimitiveComponent* ComponentToGrab;

	FHitResult ResultItem;

	UPROPERTY(EditAnyWhere)
		float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	FHitResult GetFirstPhysicsBodyInReach(FHitResult& ResultItem) const;

	
};
