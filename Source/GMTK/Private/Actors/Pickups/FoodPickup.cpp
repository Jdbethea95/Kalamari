// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/FoodPickup.h"


AFoodPickup::AFoodPickup()
{

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetCollisionProfileName("NoCollision"); //to prevent bullet collisions
	SkeletalMeshComponent->SetupAttachment(BoxCollider);
	scale = 0.38f;
	PickupSize = ObjectSize::OS_Small;
}

void AFoodPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AFoodPickup::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickupInterface* PickupActor = Cast<IPickupInterface>(OtherActor);
	if (PickupActor && PickupActor->CanPickup(PickupSize))
	{
		HandlePickup(OtherActor, SweepResult);
		HandlePostPickup();
	}
}

void AFoodPickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
	IPickupInterface* PickupActor = Cast<IPickupInterface>(OtherActor);

	if (PickupActor != nullptr)
	{
			PickupActor->HandlePickup(scale);
	}
}

void AFoodPickup::HandlePostPickup()
{
	Super::HandlePostPickup();
	//Destroy();
}
