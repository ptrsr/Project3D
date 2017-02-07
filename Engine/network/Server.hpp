#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <iostream>

#include <Windows.h>
#include <stdio.h>

using namespace std;

class Server
{
public:
	Server(int port, int maxClients);
	~Server();

	int StartServer();
	int StopServer();

private:
	SOCKET _sock; //Socket we will use
	SOCKET _sockClient[4]; //Sockets to send/receive clients
	SOCKADDR_IN _iSock; //Contains info about us
	SOCKADDR_IN _iSockClient; //Contains info about the client
	WSADATA _data; //Save our socket version
	int _clients = 0; //Used for accepting clients
	int _port; //The port our server will run on
	int _maxClients = 4; //Max amount of clients we will accept

	int AcceptClients();

	int Send(char* buf, int len, int client);
	int Receive(char* buf, int len, int client);
};