#include "../network/Server.hpp"

#include <sstream>
#include <cereal/archives/binary.hpp>

#include "../network/NetworkCommand.hpp"
#include "../network/Data.hpp"
#include "../network/PlayerData.hpp"
#include "../network/TileData.hpp"
#include "../network/ScoreData.hpp"

#include "mge/core/GameObject.hpp"

Server::Server(int port, int maxClients) : _port(port), _maxClients(maxClients)
{
	memset(_sockClient, 0, sizeof(_sockClient)); //Set all values to 0

	/*
	GameObject* o = new GameObject("o", glm::vec3(5, 1, 7));
	PlayerData* pd = new PlayerData(); //Instantiate
	pd->transform = o->getTransform(); //Assign value
	Data* d = pd; //Cast to Data
	PlayerData* ppd = dynamic_cast<PlayerData*>(d); //Cast to Derived
	*/
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
	_sock = socket(AF_INET, SOCK_STREAM, 0); //Set socket type to IPv4

	if (_sock == INVALID_SOCKET)
	{
		cout << "ERROR: Invalid socket" << endl;
		Sleep(4000);
		exit(0);
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
		return 0;
	}
	cout << "Socket binding succesful" << endl;

	cout << "Listening to socket.." << endl;
	err = listen(_sock, 4); //Listen to our socket with a client limit of 4
	if (err == SOCKET_ERROR)
	{
		cout << "ERROR: Socket listening error" << endl;
		return 0;
	}
	cout << "Socket listening succesful" << endl;

	cout << "Server succesfully started" << endl;
	_running = true;

	//Start threads for accepting and handling clients
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

	while (_running)
	{
		cout << "Waiting for clients.." << endl;
		int clientInfoSize = sizeof(_iSockClient);
		SOCKET client = accept(_sock, (sockaddr*)&_iSockClient, &clientInfoSize); //Accept clients, getting their socket info and socket info size

		if (client == INVALID_SOCKET)
		{
			cout << "ERROR: Client invalid socket" << endl;
			continue;
		}

		cout << "A client has joined the server(IP: " << inet_ntoa(*(struct in_addr*)&_iSock.sin_addr.s_addr) << ")" << endl;

		if (_clients < _maxClients)
		{
			//Notify the client the connection has been accepted
			netCode = CONNECTION_ACCEPTED;

			if (Send((char*)&netCode, sizeof(netCode), client) != 1)
			{
				cout << "Client has succesfully connected" << endl;
				_sockClient[_clients] = client; //Save the socket
				_clients++; //Update connected clients
			}
			else
			{
				cout << "Client failed to connect" << endl;
			}
		}
		else
		{
			//Notify the client the server is full
			netCode = SERVER_FULL;

			Send((char*)&netCode, sizeof(netCode), client);
			CloseConnection(client);
		}
	}
}

void Server::HandleClients()
{
	while (_running)
	{
		for (int i = 0; i < _maxClients; i++)
		{
			if (_sockClient[i] == 0)
				continue;

			char data[sizeof(Data)];
			if (Receive(data, sizeof(Data), i) == 1)
				continue;

			istringstream is(reinterpret_cast<char const*>(data));

			Data* d = new Data();
			{
				cereal::BinaryInputArchive ar(is);

				ar(*d);
			}
			
			//PlayerData pData = static_cast<PlayerData>(d);

			GameObject* t = new GameObject("t", glm::vec3(0, 0, 0));
			//t->setTransform(pData.transform);

			cout << t->getLocalPosition() << endl;
		}
	}
}

//
//Send
//
int Server::Send(char* buf, int len, SOCKET client)
{
	int dataLen = _WINSOCKAPI_::send(client, buf, len, 0); //Sends a char buffer to the client with a length and flag 0
	if (dataLen < 0)
	{
		cout << "ERROR: Failed to send data" << endl;
		return 1;
	}
	return dataLen;
}

int Server::Send(char* buf, int len, int clientId)
{
	int dataLen = _WINSOCKAPI_::send(_sockClient[clientId], buf, len, 0); //Sends a char buffer to the client with a length and flag 0
	if (dataLen < 0)
	{
		cout << "ERROR: Failed to send data to client " << clientId << endl;
		return 1;
	}
	return dataLen;
}

//
//Receive
//
int Server::Receive(char* buf, int len, SOCKET client)
{
	int dataLen = _WINSOCKAPI_::recv(client, buf, len, 0); //Receive a char buffer from the client with a length and flag 0
	if (dataLen < 0)
	{
		cout << "ERROR: Failed to receive data" << endl;
		return 1;
	}
	return dataLen;
}

int Server::Receive(char* buf, int len, int clientId)
{
	int dataLen = _WINSOCKAPI_::recv(_sockClient[clientId], buf, len, 0); //Receive a char buffer from the client with a length and flag 0
	if (dataLen < 0)
	{
		cout << "ERROR: Failed to receive data from client " << clientId << endl;
		return 1;
	}
	return dataLen;
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
	closesocket(_sockClient[clientId]);
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