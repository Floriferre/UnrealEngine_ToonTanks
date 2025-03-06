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
	
private:
	UPROPERTY(VisibleAnywhere, Category="Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category="Components")
	class UCameraComponent* Camera;
	
};
