// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// 탱크까지의 거리 구하기
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		// 탠크가 사정거리에 있는지 확인하기
		if (Distance <= FireRange)
		{
			// 사정거리 내에 있다면 Turret을 회전하기
			RotateTurret(Tank->GetActorLocation());		
		}
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	// APawn이 상위 클래스이므로 Cast 필요 
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
} 