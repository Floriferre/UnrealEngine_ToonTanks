// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
	// 스프링 암 만들어서 루트 컴포넌트에 연결하기 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	// 카메라 만들어서 스프링암에 연결하기
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	// AController가 상위 타입의 오브젝트
	// 상위 타입의 오브젝트를 하위타입의 오브젝트인 APlayerController에 저장할 수 없다
	// 따라서 Cast를 해주어야한다
	// 플레이어가 사용하고 있는 캐릭터를 리턴
	TankPlayerController = Cast<APlayerController>(GetController());
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 인풋된 값을 가져오는데, MoveForward로 바인드, 어디에? Tank에, 어디로? Move로 
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);	// D, A 눌렀을 때

	// Action Mapping (Action은 여러번 동작 가능)
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);;
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint,25.f, 12, FColor::Red, false, -1.0f);
		RotateTurret(HitResult.ImpactPoint);	// 마우스가 가리키는 정확한 위치를 넘겨주어 turret을 회전시킨다 
	}
}

// BasePawn 것을 상속 받아 사용 
void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);	// Destroy하는 대신 화면에서만 숨기기
	SetActorTickEnabled(false);	// Tick 금지
}

void ATank::Move(float value)
{
	FVector DeltaLocation = FVector::ZeroVector;	// DeltaLocation 초기화
	// X = Value * DeltaTime * Speed
	DeltaLocation.X = value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);	// value 할당 * Speed 조절 * 현재 Tank가 있는 World의 DeltaTime을 가져옴
	AddActorLocalOffset(DeltaLocation, true);	// Offset 적용
}

void ATank::Turn(float value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;	// Rotator 초기화 
	// Y = Value * DeltaTime * Speed
	DeltaRotation.Yaw = value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);	// value 할당 * TurnRate 조절 * 현재 Tank가 있는 World의 DeltaTime을 가져옴
	AddActorLocalRotation(DeltaRotation, true);	
}
