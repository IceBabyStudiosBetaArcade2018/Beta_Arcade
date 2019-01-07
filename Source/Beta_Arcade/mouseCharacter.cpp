// Fill out your copyright notice in the Description page of Project Settings.

#include "mouseCharacter.h"
#include "Components/InputComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "Engine.h"


// Sets default values
AmouseCharacter::AmouseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 200.f;

}

// Called when the game starts or when spawned
void AmouseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AmouseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//rotatePlayer();

}

// Called to bind functionality to input
void AmouseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	//AXIS BINDINGS
	InputComponent->BindAxis("MoveForward", this, &AmouseCharacter::moveLocalX); // "Move Forward" will pass scale no. defined in engine into the speed float val of function"
	InputComponent->BindAxis("MoveRight", this, &AmouseCharacter::moveLocalY);
	InputComponent->BindAxis("TurnRate", this, &AmouseCharacter::turnPlayer);

	//ACTION BINDINGS
	//PROJECT SETTING NAME, BUTTON PRESS TYPE, ACTOR AFFECTED, FUNCTION TO CALL
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump); //label must match project settings
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AmouseCharacter::startSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AmouseCharacter::endSprint);
}

void AmouseCharacter::moveLocalX(float speed)
{
	if (Controller && speed) //if the defined key is pressed
	{
		AddMovementInput(GetActorForwardVector(), speed); //move actor forward direction at speed defined by "scale" in PS
	}
}

void AmouseCharacter::moveLocalY(float speed)
{
	if (Controller && speed)
	{
		AddMovementInput(GetActorRightVector(), speed);
	}
}

void AmouseCharacter::turnPlayer(float speed)
{
	if (controller && speed)
	{
		AddControllerYawInput(speed * GetWorld()->GetDeltaSeconds());
	}
}

void AmouseCharacter::rotatePlayer()
{
	float mouseX{0};
	float mouseY{0};

	controller->GetMousePosition(mouseX, mouseY); //assigns mouse pos to defined float vals

	FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY()); //gets the width of the screen

	//IF STATEMENT PREVENTS MOUSE CLAMPING TO SCREEN (PREVENTS ROTATION BEING DEPENDENT ON SCREEN SIZE) - NEEDS FIXING/TWEAKING
	//if (mouseX == 0)
	//{
	//	controller->SetMouseLocation(viewportSize.X, mouseY);
	//}
	//else if (mouseX >= viewportSize.X - 1)
	//{
	//	controller->SetMouseLocation(0, mouseY);
	//}

	FRotator rot{ 0, mouseX, 0 };
	SetActorRotation(rot);

	//output varaible on screen as debug message
	//FString outputVar = FString::SanitizeFloat(viewportSize.X);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, outputVar);

}

void AmouseCharacter::startSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void AmouseCharacter::endSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}