// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;	// Projectile은 굳이 매 초마다 부를 필요가 없으니 Tick은 false로
	
	// Mesh 설정
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	// 발사체 움직임 설정. 초기 속도 = 최대 속도 
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Delegate를 생성자에 넣는 것은 Delegate가 바인드 되기 전일 수도 있으므로 너무 빠르다.
	// -> BeginPlay() 에서 넣기 
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Hit이 발생했을 때
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 현재 이 Projectile의 주체 
	auto MyOwner = GetOwner();
	if (!MyOwner)	// 주체가 없으면 패스
	{
		return;
	}
	
	// 플레이어와 데미지 타입을 가져옴 가져옴
	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	// 다른 액터가 있고, 자기 자신한테 부딪한 게 아니고, 내 주체와 부딪힌 것도 아니라면 데미지 적용 
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		Destroy();	// 맞춘 총알은 파괴해서 없애기 
	}
	
}

