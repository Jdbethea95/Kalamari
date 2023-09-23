// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/PickupBase.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	SetRootComponent(BoxCollider);

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnCollisionBegin);

}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupBase::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{

}

void APickupBase::HandlePostPickup()
{
	Destroy();
}

void APickupBase::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandlePickup(OtherActor, SweepResult);
	HandlePostPickup();
}


