// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 생성자에서 오브젝트 생성 
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;	// 루트 컴포넌트로 지정

	// 탱크 몸체 만들어서 루트 컴포넌트에 붙이기
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	// 회전체 만들어서 몸체에 붙이기
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	// 총알이 발사되는 부분 만들어서 회전체에 붙이기 
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	// 방향 벡터 중에 x, y 방향만 움직이고 (Yaw) 위아래는 움직이지 않기 
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
	TurretMesh->SetWorldRotation(	// 부드럽게 움직이기 위해(기존에는 탱크 가운데 부분에서 머리가 휙휙 움직였다) 간섭 추가 
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			15.f)
		);	// Rotation 반영하기 
}

void ABasePawn::Fire()
{
	// 발사체 위치 
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	// Projectile 생성
	// auto : 컴파일 시간에 그 변수의 타입을 자동으로 추론함
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass,
		Location,
		Rotation
	);
	Projectile->SetOwner(this);	// Projectile의 Owner는 Pawn
	
}


