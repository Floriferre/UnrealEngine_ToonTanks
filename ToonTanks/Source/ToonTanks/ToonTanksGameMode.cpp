// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)	// 탱크가 죽었으면 
	{
		Tank->HandleDestruction();	// 핸들러를 없애고 
		if (ToonTanksPlayerController)	// 컨트롤러가 있으면
		{
			// PlayerController로 Refactoring
			ToonTanksPlayerController->SetPlayerEnableState(false);
		}
	}else if (ATower* DestroyedTower = Cast<ATower>(DeadActor)){	// () 안에 선언한 것을 바로 가져다 쓸 수 있다 
		DestroyedTower->HandleDestruction();
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

// 게임이 바로 시작하지 않고 일정시간 딜레이 후 시작되게 
void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));	// 현재 월드에서 0번쨰 인덱스 가져오기
	// Player Controller 설정 
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnableState(false);	// 일단 바로 게임 시작 X

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnableState,
			true
		);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,	// delay
			false	// loop X
			);
	}
	
}

