// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/CharacterBase.h"
#include "Widgets/BaseHUD.h"
#include "NiagaraComponent.h"
#include "PlayerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVFX);

/**
 *
 */
UCLASS()
class GMTK_API APlayerBase : public ACharacterBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpringArmComponent* springArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* cameraComponent;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Variable|Class Ref")
		TSubclassOf<UBaseHUD>HUDBase;
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnMunch"), Category = "MUNCH")
		FVFX OnMunch;
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnTimeEnd"), Category = "OnEnd")
		FVFX OnTimeEnd;
public:
	APlayerBase();
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	virtual void CharacterDeath(float Ratio) override;

private:
	//Controller Functions and Variables
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	APlayerController* PController;

	//HUD Private Variables
	UUserWidget* PlayerWidget;
	UBaseHUD* PlayerHUD;

	//HUD Timer
	void HandleTime();
	FTimerHandle HudTimeHandle;
	int minutes;
	int seconds;

	//Scaling Functions and Variables
	bool isGrowing;
	void GrowBigAndStrong(float deltaTime);
	FVector currentScale;
	FVector newScale;

	FVector currentColliderScale;
	FVector newColliderScale;

	float scalingSpeed;

	float currentArmLength;
	float newArmLength;

public:

	//Start IPickupInterface
	bool CanPickup(ObjectSize OtherActorSize) override;
	bool HandlePickup(float scale) override;
	ObjectSize PlayerSize;
	//End IPickupInterface
};
