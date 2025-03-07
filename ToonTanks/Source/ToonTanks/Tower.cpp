// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (InFireRange())
	{
		// 사정거리 내에 있다면 Turret을 회전하기
		RotateTurret(Tank->GetActorLocation());		
	}
}

void ATower::HandleDestruction()
{
	// BasePawn의 Sound, Effect를 상속받아서 사용 후 Destroy
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	// APawn이 상위 클래스이므로 Cast 필요 
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// 타이머 설정 : 타이머 핸들러로 FireRate마다 작동하게 
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ATower::CheckFireCondition,
		FireRate,
		true);
}


void ATower::CheckFireCondition()
{
	if (InFireRange())
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}