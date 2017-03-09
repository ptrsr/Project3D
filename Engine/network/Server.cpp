#include "../network/Server.hpp"

#include "../network/PacketHelper.hpp"
#include "../game/Level.hpp"

Server::Server(int port, int maxClients) : _port(port), _maxClients(maxClients)
{

}

Server::~Server()
{

}

//
//Start Server
//
int Server::StartServer()
{
	cout << "Starting server.." << endl;
	int err;

	cout << "Creating socket.." << endl;
	WSAStartup(MAKEWORD(2, 2), &_data); //Initialize socket and set version to 2.2
	_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Set socket type to IPv4, TCP protocol

	if (_sock == INVALID_SOCKET)
	{
		PacketHelper::ErrorHandler();
		WSACleanup();
		return 0;
	}

	cout << "Socket creation succesful" << endl;

	cout << "Assigning socket info.." << endl;
	_iSock.sin_family = AF_INET; //Family type to IPv4
	_iSock.sin_addr.s_addr = htonl(INADDR_ANY); //Set the server to our IP
	_iSock.sin_port = htons(_port); //Set the server port

	cout << "Applied socket info" << endl;

	cout << "Binding socket.." << endl;
	err = _WINSOCKAPI_::bind(_sock, (LPSOCKADDR)&_iSock, sizeof(_iSock)); //Bind the socket, giving it's info and size
	
	if (err != 0)
	{
		PacketHelper::ErrorHandler();
		StopServer();
		return 0;
	}
	cout << "Socket binding succesful" << endl;

	//Time-out struct
	timeval tv;
	tv.tv_sec = _timeOut;

	//Apply time-out to socket
	setsockopt(_sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof(tv));
	setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));
	
	cout << "Listening to socket.." << endl;
	err = listen(_sock, _maxClients); //Listen to our socket with a client limit of 3

	if (err == SOCKET_ERROR)
	{
		PacketHelper::ErrorHandler();
		StopServer();
		return 0;
	}
	cout << "Socket listening succesful" << endl;

	cout << "Server succesfully started" << endl;
	cout << "Server IP: " << inet_ntoa(_iSock.sin_addr) << ":" << _port << endl;
	_running = true;

	thread acceptClients(&Server::AcceptClients, this); //Start thread for accepting clients
	acceptClients.join(); //Join it with the main thread

	return 0;
}

//
//Stop Server
//
int Server::StopServer()
{
	cout << "Stopping server.." << endl;
	_running = false; //Stop all loops
	closesocket(_sock); //Close our socket
	WSACleanup(); //Clean up everything
	cout << "Server stopped" << endl;
	return 1;
}

//
//Send
//
void Server::SendAll(DataType type, char* data)
{
	NotifyClients(type, data);
}

//
//Connected Count
//
int Server::ConnectedCount()
{
	return _connectedClients;
}

//
//Changes the ready count
//
void Server::AddReadyCount(bool value)
{
	if (value)
		_readyCount++;
	else
		_readyCount--;

	CountReady();
}

//
//Saving client to the list
//
void Server::SaveSocket(SOCKET client)
{
	for (int i = 0; i < _sockClients.size(); i++)
	{
		//Check if there is a empty slot from a leaver
		if (_sockClients[i] == 0)
		{
			//Overwrite the spot with the new client
			_sockClients[i] = client;
			return;
		}
	}

	//Add client to the list
	_sockClients.push_back(client);
}

//
//Returns id of client in the client list
//
int Server::GetClientId(SOCKET client)
{
	for (int i = 0; i < _sockClients.size(); i++)
	{
		if (_sockClients[i] == client)
		{
			return i; //Client found
		}
	}

	cout << "ERROR: Client not found" << endl;
	return -1; //Client not found
}

//
//Accept Clients
//
void Server::AcceptClients()
{
	NetWorkCommand netCode; //Connection code

	cout << "Waiting for clients.." << endl;

	while (_running)
	{
		int clientInfoSize = sizeof(_iSockClient);
		SOCKET client = accept(_sock, (sockaddr*)&_iSockClient, &clientInfoSize); //Accept clients, getting their socket info and socket info size

		if (client == INVALID_SOCKET)
		{
			cout << "ERROR: Client invalid socket" << endl;
			continue;
		}

		cout << "A client has joined the server(ID: " << client << " IP: " << inet_ntoa(*(struct in_addr*)&_iSock.sin_addr.s_addr) << ")" << endl;

		if (_connectedClients < _maxClients)
		{
			//Notify the client the connection has been accepted
			netCode = CONNECTION_ACCEPTED;

			if (PacketHelper::Send(DataType::NETWORKCMD, (char*)&netCode, client) != 1)
			{
				cout << "Client has succesfully connected" << endl;
				SaveSocket(client); //Save the socket
				
				thread handleClient(&Server::HandleClients, this, client); //Start thread for handling the client
				handleClient.detach(); //Let the thread live on it's own

				_connectedClients++; //Update connected clients
				cout << "Connected clients : " << _connectedClients << endl;
			}
			else
			{
				cout << "Client failed to connect" << endl;
			}
		}
		else
		{
			cout << "Connection declined, server is full" << endl;

			//Notify the client the server is full
			netCode = SERVER_FULL;

			PacketHelper::Send(DataType::NETWORKCMD, (char*)&netCode, client);
			CloseConnection(client);
		}
	}
}

void Server::HandleClients(SOCKET client)
{
	SendGameState(client); //Send game state to client

	while (_running)
	{
		if (Level::get()->checkIfFinished())
			continue;

		//Check if the client is still connected
		if (!PacketHelper::Connected( client))
		{
			cout << "Client id: " << client << endl;
			CloseClientConnection(client);
			cout << "Connected clients : " << _connectedClients << endl;
			break;
		}

		//Attempt to receive data
		char buffer[256];
		pair<DataType, char*> data = PacketHelper::Receive(buffer, client);
		HandlePacket(data.first, data.second);
	}
}

void Server::HandlePacket(DataType type, char* buf)
{
	switch (type)
	{
	case DataType::MOVEDATA:
		MoveData moveData = *reinterpret_cast<MoveData*>(buf);
		{
			Level* level = Level::get();
			Player* player = level->getPlayers()[moveData.playerId - 1];
			player->_movement->SetDDir(moveData.direction);
			glm::vec2 curPos = player->_movement->getBoardPos();
			
			moveData.boardX = curPos.x;
			moveData.boardY = curPos.y;

			NotifyClients(DataType::MOVEDATA, (char*)&moveData);
		}
		break;
	case DataType::USEDATA:
		UseData useData = *reinterpret_cast<UseData*>(buf);
		Level::getPlayer(useData.playerId)->_movement->activate = true;
		break;
	case DataType::READYDATA:
		ReadyData readyData = *reinterpret_cast<ReadyData*>(buf);
		Level::get()->GetLobbyState()->UpdateVisual(readyData.playerId, readyData.ready);
		NotifyClients(DataType::READYDATA, (char*)&readyData);
		AddReadyCount(readyData.ready);
		break;
	}
}

void Server::NotifyClients(DataType type, char* data)
{
	for (int i = 0; i < _sockClients.size(); i++)
	{
		if (_sockClients[i] == 0)
			continue;

		//Send data to the client
		PacketHelper::Send(type, data, _sockClients[i]);
	}
}

void Server::CountReady()
{
	if (_readyCount == 2)
	{
		Level::get()->ResetStatues();

		StartData sd;
		sd.start = true;
		NotifyClients(DataType::STARTDATA, (char*)&sd); //Give the start sign

		Level::get()->Start(sd.start); //Start our game too
	}
}

//
//Send Game State
//
void Server::SendGameState(SOCKET client)
{
	Level* level = Level::get();

	vector<Player*> players = level->getPlayers();

	//Send current player positions
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i] == NULL)
			continue;

		Player* player = players[i];
		PlayerData pData;
		pData.playerId = player->getId();
		pData.controlled = false;
		pData.boardX = player->getBoardPos().x;
		pData.boardY = player->getBoardPos().y;
		SendAll(DataType::PLAYERDATA, (char*)&pData);
	}

	//Send client player id and pos
	PlayerData cData;
	cData.playerId = static_cast<Id>(GetClientId(client) + 2);
	pair<int, int> spawnPos = level->GetSpawnPosition(cData.playerId);
	cData.controlled = true;
	cData.boardX = spawnPos.first;
	cData.boardY = spawnPos.second;

	PacketHelper::Send(DataType::PLAYERDATA, (char*)&cData, client);
	cData.controlled = false;
	NotifyClients(DataType::PLAYERDATA, (char*)&cData);
	level->AddSpawn(cData);
}

//
//Close Connection
//
void Server::CloseConnection(SOCKET client)
{
	closesocket(client); //Closes a client's connection
}

void Server::CloseClientConnection(SOCKET client)
{
	closesocket(client); //Closes a client's connection
	for (int i = 0; i < _sockClients.size(); i++)
	{
		if (_sockClients[i] == client)
		{
			//Mark left player for deletion and notify clients
			LeaveData ld;
			ld.playerId = static_cast<Id>(i + 2);
			Level::get()->AddLeave(ld);
			NotifyClients(DataType::LEAVEDATA, (char*)&ld);

			_sockClients[i] = 0; //Overwrite the socket to 0 for future use
			break;
		}
	}

	_connectedClients--; //Update current connected clients
}