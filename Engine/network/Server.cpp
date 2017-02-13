#include "../network/Server.hpp"

#include "../network/PacketHelper.hpp"

#include "mge/core/GameObject.hpp"

Server::Server(int port, int maxClients) : _port(port), _maxClients(maxClients)
{

}

Server::~Server()
{

}

int Server::StartServer()
{
	cout << "Starting server.." << endl;
	int err;

	cout << "Creating socket.." << endl;
	WSAStartup(MAKEWORD(2, 2), &_data); //Initialize socket and set version to 2.2
	_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Set socket type to IPv4, TCP protocol

	//Enable non-blocking
	u_long nonBlocking = 1;
	ioctlsocket(_sock, FIONBIO, &nonBlocking);

	if (_sock == INVALID_SOCKET)
	{
		cout << "ERROR: Invalid socket" << endl;
		WSACleanup();
		return 0;
	}

	cout << "Socket creation succesful" << endl;

	cout << "Assigning socket info.." << endl;
	_iSock.sin_family = AF_INET; //Family type to IPv4
	_iSock.sin_addr.s_addr = inet_addr("127.0.0.1");// htonl(INADDR_ANY); //Set the server to our IP
	_iSock.sin_port = htons(_port); //Set the server port

	cout << "Applied socket info" << endl;

	cout << "Binding socket.." << endl;
	err = _WINSOCKAPI_::bind(_sock, (LPSOCKADDR)&_iSock, sizeof(_iSock)); //Bind the socket, giving it's info and size
	
	if (err != 0)
	{
		cout << "ERROR: Socket binding failed" << endl;
		StopServer();
		return 0;
	}
	cout << "Socket binding succesful" << endl;

	cout << "Listening to socket.." << endl;
	err = listen(_sock, _maxClients); //Listen to our socket with a client limit of 3
	if (err == SOCKET_ERROR)
	{
		cout << "ERROR: Socket listening error" << endl;
		StopServer();
		return 0;
	}
	cout << "Socket listening succesful" << endl;

	cout << "Server succesfully started" << endl;
	_running = true;

	//Start threads for accepting clients
	thread acceptClients(&Server::AcceptClients, this);
	thread handleClients(&Server::HandleClients, this);
	//Join threads
	acceptClients.join();
	handleClients.join();

	return 0;
}

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
			//cout << "ERROR: Client invalid socket" << endl;
			continue;
		}

		cout << "A client has joined the server(IP: " << inet_ntoa(*(struct in_addr*)&_iSock.sin_addr.s_addr) << ")" << endl;

		if (_connectedClients < _maxClients)
		{
			//Notify the client the connection has been accepted
			netCode = CONNECTION_ACCEPTED;

			if (PacketHelper::Send(DataType::NETWORKCMD, (char*)&netCode, client) != 1)
			{
				cout << "Client has succesfully connected" << endl;
				_sockClients.push_back(client); //Save the socket

				_connectedClients++; //Update connected clients
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

void Server::HandleClients()
{
	while (_running)
	{
		//Check data from each client
		for (int i = 0; i < _sockClients.size(); i++)
		{
			//Check if the client is still connected
			if (!PacketHelper::Connected(_sockClients[i]))
			{
				cout << "Client id: " << i << endl;
				CloseConnection(i);
				continue;
			}

			//Attempt to receive data
			char buffer[256];
			pair<DataType, char*> data = PacketHelper::Receive(buffer, _sockClients[i]);
			HandlePacket(data.first, data.second);
		}
	}
}

void Server::HandlePacket(DataType type, char* buf)
{
	switch (type)
	{
	case DataType::TESTDATA:
		TestData testData = *reinterpret_cast<TestData*>(buf);
		cout << testData.t << " " << testData.r << " " << testData.g << " " << testData.b << " " << testData.a << endl;
		cout << testData.input << endl;
		break;
	case DataType::PLAYERDATA:
		{
			PlayerData* playerData = reinterpret_cast<PlayerData*>(buf);
			switch (playerData->direction)
			{
			case Direction::up:
				cout << "up" << endl;
				break;
			case Direction::down:
				cout << "down" << endl;
				break;
			case Direction::left:
				cout << "left" << endl;
				break;
			case Direction::right:
				cout << "right" << endl;
				break;
			}
		}
		break;
	}
}

void Server::NotifyClients(DataType type, char*, int fromClientId)
{

}

//
//Close Connection
//
void Server::CloseConnection(SOCKET client)
{
	closesocket(client); //Closes a client's connection
}

void Server::CloseConnection(int clientId)
{
	closesocket(_sockClients[clientId]); //Closes a client's connection
	_sockClients.erase(_sockClients.begin() + clientId); //Removes the client from the list
	_connectedClients--; //Update current connected clients
}

//
//Stop Server
//
int Server::StopServer()
{
	cout << "Stopping server.." << endl;
	closesocket(_sock); //Close our socket
	WSACleanup(); //Clean up everything
	cout << "Server stopped" << endl;
	return 1;
}