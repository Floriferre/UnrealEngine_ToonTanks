// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * // BasePawn 클래스를 상속받음
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn	
{
	GENERATED_BODY()

public:
	ATank();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Getter function of APlayerController 
	APlayerController* GetTankPlayerController() const {return TankPlayerController;}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
private:
	UPROPERTY(VisibleAnywhere, Category="Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category="Components")
	class UCameraComponent* Camera;

	
	UPROPERTY(EditAnywhere, Category="Movement")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category="Movement")
	float TurnRate = 45.f;

	void Move(float value);
	void Turn(float value);


	APlayerController* TankPlayerController;
	
	
	
	
};
