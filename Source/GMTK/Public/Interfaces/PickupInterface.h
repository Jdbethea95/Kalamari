// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupInterface.generated.h"


UENUM(BlueprintType)
enum class ObjectSize : uint8 
{
	OS_Small UMETA(DisplayName="Small"),
	OS_Medium UMETA(DisplayName="Medium"),
	OS_Large UMETA(DisplayName="Large")
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UPickupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GMTK_API IPickupInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
		virtual bool CanPickup(ObjectSize OtherActorSize) = 0;
	UFUNCTION(BlueprintCallable)
		virtual bool HandlePickup(float scale) = 0;
};
