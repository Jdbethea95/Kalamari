// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PlayerBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"



APlayerBase::APlayerBase()
{
	//Seting up SpringArm
	PrimaryActorTick.bCanEverTick = true;
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComponent"));
	springArmComponent->SetupAttachment(GetRootComponent());
	springArmComponent->SetRelativeLocation(FVector(0.0f, 05.0f, 90.0f));
	springArmComponent->TargetArmLength = 500.0f;
	springArmComponent->bUsePawnControlRotation = true;

	//Setting up Camera
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraComponent"));
	cameraComponent->SetupAttachment(springArmComponent);
	cameraComponent->SetAbsolute(false, false, true); //Scales separately from collider root
	GetMesh()->SetAbsolute(false, false, true);


	//Setting up Collider Scale to fit Mesh Better
	GetCapsuleComponent()->SetWorldScale3D(FVector(1.5f, 1.5f, 0.5f));


	//Set Minutes and Seconds, Will set to a SetTime function for later use if needed
	minutes = 1;
	seconds = 02;

	//grabs initial scale and saves for later use inside HandlePickup
	currentScale = GetMesh()->GetRelativeScale3D();
	newScale = currentScale;

	currentColliderScale = GetCapsuleComponent()->GetRelativeScale3D();
	newColliderScale = currentColliderScale;
	scalingSpeed = 2.0f;
	isGrowing = false;

}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	PController = Cast<APlayerController>(this->GetController());
	GetWorldTimerManager().SetTimer(HudTimeHandle, this, &APlayerBase::HandleTime, 1.0f, false);
	//Clamps Camera Pitch from ground to slightly above character
	if (PController != nullptr)
	{

		PlayerWidget = CreateWidget(PController, HUDBase);
		PlayerWidget->AddToViewport();

		PlayerHUD = Cast<UBaseHUD>(PlayerWidget);
		PlayerHUD->ModifyTimer(minutes, seconds);
		if (PController->PlayerCameraManager)
		{
			PController->PlayerCameraManager->ViewPitchMax = 15.0f;
			PController->PlayerCameraManager->ViewPitchMin = -65.0f;

		}
	}


	//Sets player size to small
	PlayerSize = ObjectSize::OS_Small;
}

void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Mouse Inputs for SpringArm and Camera
	PlayerInputComponent->BindAxis("LookRight", this, &APlayerBase::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerBase::AddControllerPitchInput);
	//WASD Inputs based on Camera Direction
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerBase::MoveRight);
}

void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isGrowing)
	{
		//UE_LOG(LogTemp, Error, TEXT("Entered"));
		GrowBigAndStrong(DeltaTime);
	}

	if (!GetWorldTimerManager().IsTimerActive(HudTimeHandle))
	{
		GetWorldTimerManager().SetTimer(HudTimeHandle, this, &APlayerBase::HandleTime, 1.0f, false);
	}


}

void APlayerBase::CharacterDeath(float Ratio)
{
	Super::CharacterDeath(Ratio);
	DisableInput(PController);
}


//Movement Functions
void APlayerBase::MoveForward(float AxisValue)
{
	FRotator MakeRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	AddMovementInput(MakeRotator.Vector(), AxisValue, false); //default optional false value utilized!
}

void APlayerBase::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue, false);
}

//Scaling Function
void APlayerBase::GrowBigAndStrong(float deltaTime)
{

	if (currentArmLength >= (newArmLength - 0.2f))
	{
		newArmLength = currentArmLength;
		newScale = currentScale;
		isGrowing = false;
	}
	else
	{
		currentScale = currentScale + (newScale - currentScale) * deltaTime * scalingSpeed;
		GetMesh()->SetWorldScale3D(currentScale);
		currentColliderScale = currentColliderScale + (newColliderScale - currentColliderScale) * deltaTime * scalingSpeed;
		GetCapsuleComponent()->SetWorldScale3D(currentColliderScale);
		currentArmLength = currentArmLength + (newArmLength - currentArmLength) * deltaTime * scalingSpeed;
		springArmComponent->TargetArmLength = currentArmLength;
		//UE_LOG(LogTemp, Error, TEXT("%f"), deltaTime);
	}
	
	UE_LOG(LogTemp, Error, TEXT("%f"), newScale.X);
	if (newScale.X >= 1.5f && newScale.X <= 2.5f)
		PlayerSize = ObjectSize::OS_Medium;
	else if (newScale.X >= 2.5 && PlayerSize != ObjectSize::OS_Large)
		PlayerSize = ObjectSize::OS_Large;
}

//Hud Timer Functions
void APlayerBase::HandleTime()
{
	seconds--;
	if (seconds < 0 && minutes > 0)
	{
		seconds = 59;
		minutes--;
	}
	if (seconds <= 0 && minutes <= 0)
	{
		minutes = 0; seconds = 0;
		OnTimeEnd.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("Beat The Timer"));
	}

	PlayerHUD->ModifyTimer(minutes, seconds);
}

//Pickup Interface Functions
bool APlayerBase::CanPickup(ObjectSize OtherActorSize)
{
	//Wonder if enums still hold thier number values... <.<
	if (PlayerSize >= OtherActorSize) //wow... huh...there is no way this works right...
		return true;
	else
		return false;
}

bool APlayerBase::HandlePickup(float scale)
{

	if (newScale == currentScale)
	{
		OnMunch.Broadcast();
		newScale = currentScale + scale;
		newColliderScale = currentColliderScale + (scale * 0.25f);
		currentArmLength = springArmComponent->TargetArmLength;
		newArmLength = currentArmLength + 20.0f;
	}
	else
	{
		OnMunch.Broadcast();
		newScale = newScale + scale;
		newColliderScale = newColliderScale + (scale * 0.25f);
		newArmLength = newArmLength + 20.0f;

	}


	isGrowing = true;

	return true;
}
