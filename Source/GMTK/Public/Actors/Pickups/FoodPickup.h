// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/PickupBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Interfaces/PickupInterface.h"
#include "FoodPickup.generated.h"

/**
 *
 */
UCLASS()
class GMTK_API AFoodPickup : public APickupBase
{
	GENERATED_BODY()

public:
	AFoodPickup();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* SkeletalMeshComponent;

	//The collision function
	virtual	void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override;

	virtual void HandlePostPickup() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSize")
		ObjectSize PickupSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSize") //Value of player growth
		float scale;
private:

};
