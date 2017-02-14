#pragma once

#include <Windows.h>
#include <stdio.h>

#include <thread>
#include <iostream>

#include "../network/PacketHelper.hpp"

using namespace std;

class Client
{
public:
	Client();
	~Client();

	int Connect(char* IP, int port);
	int Disconnect();
	void Send(DataType type, char* data);
private:
	SOCKET _sock; //Our socket we will use to connect to the server
	SOCKADDR_IN _iSock; //This socket contains info about our socket
	WSADATA _data; //This is to save our socket version
	bool _connected = false;
	int _timeOut = 60000; //Time-out in mili-seconds

	void ReceiveResponse();
	void ReceiveData();
	void HandlePacket(DataType type, char* buf);
};