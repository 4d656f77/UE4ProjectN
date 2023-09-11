// Fill out your copyright notice in the Description page of Project Settings.


#include "clientSocket.h"

clientSocket::clientSocket()
{
	UE_LOG(LogNet, Warning, TEXT("clientSocket init"));
	if (ConnectServer())
	{
		_thread = FRunnableThread::Create(this, TEXT("socket Thread"));
	}
}

clientSocket::~clientSocket()
{
	if (_thread)
	{
		// Kill() is a blocking call, it waits for the thread to finish.
		//_thread->WaitForCompletion();
		_thread->Kill();
		delete _thread;
	}
}

bool clientSocket::Init()
{
	UE_LOG(LogNet, Warning, TEXT("Thread has been initialized"));
	return true;
}

uint32 clientSocket::Run()
{
	uint32 rep = 10;
	Sleep(1000);
	
	for (uint32 i = 0; i < rep; ++i)
	{
		// UE_LOG(LogNet, Warning, TEXT("Send %d"), Send());
		char buf[100] = { 0 };
		UE_LOG(LogNet, Warning, TEXT("Recv %d, %s"), Recv(buf, sizeof(buf)), buf);
	
	}
	return uint32();
}

void clientSocket::Exit()
{
	if (_socket != INVALID_SOCKET)
	{
		closesocket(_socket);
		WSACleanup();
	}
}

bool clientSocket::ConnectServer()
{
	WSADATA wsaData;
	int iResult = 0;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		UE_LOG(LogNet, Warning, TEXT("WSAStartup failed : %d"), iResult);
		return false;
	}

	_socket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == INVALID_SOCKET)
	{
		UE_LOG(LogNet, Warning, TEXT("WSASocket failed"));
		return false;
	}

	SOCKADDR_IN serverAddr;
	::ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = ::htons(7777);
	if (::connect(_socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		UE_LOG(LogNet, Warning, TEXT("connect failed"));
		return false;
	}

	UE_LOG(LogNet, Warning, TEXT("connect to server"));
	return true;
}

uint32 clientSocket::Send(char* buf, uint32 bufsize)
{
	uint32 sendLen = 0;
	sendLen = ::send(_socket, buf, bufsize, 0);

	return sendLen;
}

uint32 clientSocket::Recv(char* buf, uint32 bufsize)
{
	uint32 recvLen = 0;
	
	recvLen = ::recv(_socket, buf, bufsize, 0);

	return recvLen;
}
