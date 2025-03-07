// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetPlayerEnableState(bool bPlayerEnabled)
{
	// 플레이어가 살아있으면 Pawn의 인풋을 살리고 
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}else // 아니면 인풋을 없앤다 
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;	// 마우스 커서는 플레이어 상태 따라가기 
}
