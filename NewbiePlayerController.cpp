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
	// ƽ���� ������ �αװ� ���� ������.
	// �ɸ��� �������� ����ȭ ����
	
}


// Ÿ�̸� ���� �� �ð����� ������?
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

	// nullptr�̰ų� ��ü�� ���� ������̸� ����	
	if (!IsValid(character)) return;

	// �ɸ��� ���� ����
	const FVector& Location = character->GetActorLocation();
	const FRotator& Rotation = character->GetActorRotation();
	const FVector& Velocity = character->GetVelocity();

	// ��������
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

	// Socket���� send ȣ��
	uint32 ret = _socket->Send((char*)&buf, bufsize);
	UE_LOG(LogNet, Warning, TEXT("Send : %d BYTE"), ret);
}
