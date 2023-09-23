// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/PickupInterface.h"
#include "CharacterBase.generated.h"


UCLASS()
class GMTK_API ACharacterBase : public ACharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void CharacterDeath(float Ratio);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Start IPickupInterface
	bool CanPickup(ObjectSize OtherActorSize) override; //why do i do this to myself....
	bool HandlePickup(float scale) override;
	//End IPickupInterface

};
