// Fill out your copyright notice in the Description page of Project Settings.


#include "socket.h"

socket::socket()
{
	if (ConnectServer())
	{
		_thread = FRunnableThread::Create(this, TEXT("socket Thread"));
	}
}

socket::~socket()
{
	if (_thread)
	{
		// Kill() is a blocking call, it waits for the thread to finish.
		// _thread->WaitForCompletion();
		_thread->Kill();
		delete _thread;
	}
}

bool socket::Init()
{
	UE_LOG(LogNet, Warning, TEXT("Thread has been initialized"));
	return true;
}

uint32 socket::Run()
{
	return uint32();
}

void socket::Exit()
{
	if (_socket != INVALID_SOCKET)
	{
		closesocket(_socket);
		WSACleanup();
	}
}

bool socket::ConnectServer()
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

uint32 socket::Send()
{
	uint32 sendLen = 0;
	char buff[] = "test";
	sendLen = ::send(_socket, buff, sizeof(buff), 0);
	
	return sendLen;
}
