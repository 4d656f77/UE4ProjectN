// Fill out your copyright notice in the Description page of Project Settings.


#include "NewbiePlayerController.h"
#include "newbieCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "packets.h"

ANewbiePlayerController::ANewbiePlayerController()
{
	_socket = clientSocket::getSocket();

}

ANewbiePlayerController::~ANewbiePlayerController()
{
}

void ANewbiePlayerController::Tick(float DeltaSeconds)
{
	UE_LOG(LogNet, Warning, TEXT("Tick"));
	SendCharacterInfo();
	// 틱마다 보내면 로그가 많이 찍힌다.
	// 케릭터 물리정보 동기화 문제
	
}


// 타이머 설정 후 시간마다 보낼까?
void ANewbiePlayerController::SendCharacterInfo()
{

	// template <typename To, typename From>
	// FORCEINLINE To* Cast(From * Src)
	// {
	//	 return TCastImpl<From, To>::DoCast(Src);
	// }
	AnewbieCharacter* character = Cast<AnewbieCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
	// FORCEINLINE bool IsValid(const UObject * Test)
	// {
	// 	 return Test && !Test->IsPendingKill();
	// }

	// nullptr이거나 객체가 삭제 대기중이면 리턴	
	if (!IsValid(character)) return;

	// 케릭터 물리 정보
	const FVector& Location = character->GetActorLocation();
	const FRotator& Rotation = character->GetActorRotation();
	const FVector& Velocity = character->GetVelocity();

	// 프로토콜
	// {FVector}{FRotator}{FVector}
	struct packets::characterPhysInfo buf;
	uint32 bufsize = sizeof(packets::characterPhysInfo);
	buf.Location.X = Location.X;
	buf.Location.Y = Location.Y;
	buf.Location.Z = Location.Z;

	buf.Rotation.Pitch = Rotation.Pitch;
	buf.Rotation.Yaw = Rotation.Yaw;
	buf.Rotation.Roll = Rotation.Roll;

	buf.Velocity.X = Velocity.X;
	buf.Velocity.Y = Velocity.Y;
	buf.Velocity.Z = Velocity.Z;

	// Socket으로 send 호출
	uint32 ret = _socket->Send((char*)&buf, bufsize);
	UE_LOG(LogNet, Warning, TEXT("Send : %d BYTE"), ret);
}
