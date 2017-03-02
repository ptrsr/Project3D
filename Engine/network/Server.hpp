#pragma once

#include <iostream>
#include <vector>

#include <Windows.h>
#include <thread>
#include <algorithm>

#include "../network/packets/DataType.hpp"

using namespace std;

class Server
{
public:
	Server(int port, int maxClients);
	~Server();

	int StartServer();
	int StopServer();

	void SendAll(DataType type, char* data);

	int ConnectedCount();
private:
	SOCKET _sock; //Our socket that client's use to connect
	vector<SOCKET> _sockClients; //Sockets to send/receive clients
	SOCKADDR_IN _iSock; //Contains info about us
	SOCKADDR_IN _iSockClient; //Contains info about the client
	WSADATA _data; //Save our socket version
	int _connectedClients = 0; //Used for accepting clients
	int _port; //The port our server will run on
	int _maxClients = 3; //Max amount of clients we will accept : 3, because we count as 1 as well : limit of players = 4
	bool _running = false; //Indication if the server is running
	int _timeOut = 120000; //Time-out in mili-seconds

	void AcceptClients(); //Attempts to accept incoming clients
	void HandleClients(SOCKET client); //Receives data from all clients
	void HandlePacket(DataType type, char* buf); //Handles received packages
	void NotifyClients(DataType type, char* data, SOCKET sourceClient); //Sends data to all other clients

	void SendGameState(SOCKET client);

	void CloseConnection(SOCKET client); //Closes a client's connection attempting to join
	void CloseClientConnection(SOCKET client); //Closes a connected client's connection
};