// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"

/**
 * 
 */
class NEWBIE_API socket : public FRunnable
{
public:
	socket();
	~socket() override;
	
	// FRunnable override functions
	bool Init() override;
	uint32 Run() override;
	void Exit() override;
	
	bool ConnectServer();
	uint32 Send();

	// singleton object
	static socket* getSocket()
	{
		static socket singletonSocket;
		return &singletonSocket;
	}

private:
	SOCKET _socket = INVALID_SOCKET;
	FRunnableThread* _thread;
};
