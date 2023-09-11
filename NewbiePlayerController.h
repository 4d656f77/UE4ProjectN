// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "clientSocket.h"

#include "GameFramework/PlayerController.h"

#include "NewbiePlayerController.generated.h"


UCLASS()
class NEWBIE_API ANewbiePlayerController : public APlayerController
{
	GENERATED_BODY()
	// These macros wrap metadata parsed by the Unreal Header Tool, and are otherwise
	// ignored when code containing them is compiled by the C++ compiler
	// UPROPERTY(replicated)

public:
	ANewbiePlayerController();
	~ANewbiePlayerController();
	
	// Tick
	virtual void Tick(float DeltaSeconds) override;
	
	// 캐릭터 정보 보내기
	void SendCharacterInfo();

private:
	clientSocket* _socket = nullptr;
};
