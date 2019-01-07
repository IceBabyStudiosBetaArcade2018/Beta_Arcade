// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "mouseCharacter.generated.h"

UCLASS()
class BETA_ARCADE_API AmouseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AmouseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//void cameraPitch(float axis);
	//void cameraYaw(float axis);

	void moveLocalX(float speed); //moves player forwards/backwards
	void moveLocalY(float speed); //moves player left/right (strafe)

	void startSprint();
	void endSprint();

	void turnPlayer(float speed);

private:
	void rotatePlayer();

	FVector2D mouse;
	APlayerController* controller;
	
};
