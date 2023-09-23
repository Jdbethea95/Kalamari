// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CharacterBase.h"


ACharacterBase::ACharacterBase()
{

	PrimaryActorTick.bCanEverTick = false;

	//positions the player mesh in proper direction and height
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FQuat(FRotator(0.0f, -90.0f, 0.0f)));
}


void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACharacterBase::CharacterDeath(float Ratio)
{
}


void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ACharacterBase::CanPickup(ObjectSize OtherActorSize)
{
	return true;
}

bool ACharacterBase::HandlePickup(float scale)
{
	return true;
}

