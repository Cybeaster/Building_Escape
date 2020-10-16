// Copyright Michael Bridges 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DoorOpen.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(const float& DeltaTime);
	void ClosingTheDoor(const float& DeltaTime);
	private:

		FRotator DoorRotation;

		 float CurrentYaw;

		 float InitYaw;

		 UPROPERTY(EditAnyWhere)
		 float TargetYaw;
			
		UPROPERTY(EditAnyWhere)
		 float DoorLastOpend;

		UPROPERTY(EditAnyWhere)
		 float DoorCloseDeltaSeconds;
		 UPROPERTY(EditAnywhere)
		 ATriggerVolume* TriggerPlate;

	   	 UPROPERTY(EditAnyWhere)
	   	 AActor* ActorThatOpen;
		
	
};
