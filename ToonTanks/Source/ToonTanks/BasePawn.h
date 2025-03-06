// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	// 이 클래스에서만 접근 가능
	UPROPERTY()
	class UCapsuleComponent* CapsuleComp;
	// forward declaration (전방선언) : 헤더 파일을 포함시키는 행위가 컴파일 시간을 증가시키기 때문에 이를 막기 위해 포인터 객체를 선언할 때는 클래스 선언 전에 필요한 클래스를 명시하여 헤더파일의 중복을 막는다

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
