// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"

ATank::ATank()
{
	// 스프링 암 만들어서 루트 컴포넌트에 연결하기 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	// 카메라 만들어서 스프링암에 연결하기
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 인풋된 값을 가져오는데, MoveForward로 바인드, 어디에? Tank에, 어디로? Move로 
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
}

void ATank::Move(float value)
{
	FVector DeltaLocation = FVector::ZeroVector;	// DeltaLocation 초기화
	DeltaLocation.X = value;	// value 할당
	AddActorLocalOffset(DeltaLocation);	// Offset 적용
}
