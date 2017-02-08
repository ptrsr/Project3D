#pragma once

#include <Windows.h>
#include <stdio.h>

#include <iostream>

using namespace std;

class Client
{
public:
	Client();
	~Client();

	int Connect(char *IP, int port);
	int Disconnect();
private:
	SOCKET _sock; //Our socket we will use to connect to the server
	SOCKADDR_IN _iSock; //This socket contains info about our socket
	WSADATA _data; //This is to save our socket version
	bool _connected = false;

	bool WaitResponse();
	void ReceiveData();

	int Send(char* buf, int len);
	int Receive(char* buf, int len);
};