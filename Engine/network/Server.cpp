#include "../network/Server.hpp"

#include "../network/Packet.hpp"

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
	_iSock.sin_addr.s_addr = htonl(INADDR_ANY); //Set the server to our IP
	_iSock.sin_port = htonl(_port); //Set the server port

	cout << "Applied socket info" << endl;

	cout << "Binding socket.." << endl;
	err = bind(_sock, (LPSOCKADDR)&_iSock, sizeof(_iSock)); //Bind the socket, giving it's info and size
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

	return AcceptClients();
}

int Server::AcceptClients()
{
	while (_clients < _maxClients)
	{
		for (int i = 0; i < 4; i++) //Accept up to 4 clients at once
		{
			if (_clients < _maxClients)
			{
				cout << "Waiting for clients.." << endl;
				int clientInfoSize = sizeof(_iSockClient);
				_sockClient[_clients] = accept(_sock, (sockaddr*)&_iSockClient, &clientInfoSize); //Accept clients, getting their socket info and socket info size
				if (_sockClient[_clients] == INVALID_SOCKET)
				{
					cout << "ERROR: Client invalid socket" << endl;
					return 0;
				}
				cout << "A client has joined the server(IP: " << _iSock.sin_addr.s_addr << ")" << endl;
				_clients++;
				Sleep(1000); //Wait a bit before searching again
			}
			else
			{
				cout << "Completed searching for clients" << endl;

				//Launch game here

				break;
			}
		}
	}

	return 1;
}

int Server::Send(char* buf, int len, int client)
{
	int dataLen = send(_sockClient[client], buf, len, 0); //Sends a char buffer to the client with a length and flag 0
	if (dataLen < 0)
	{
		cout << "ERROR: Failed to send data" << endl;
		return 1;
	}
	return dataLen;
}

int Server::Receive(char* buf, int len, int client)
{
	int dataLen = recv(_sockClient[client], buf, len, 0); //Receive a char buffer from the client with a length and flag 0
	if (dataLen < 0)
	{
		cout << "ERROR: Failed to receive data" << endl;
		return 1;
	}
	return dataLen;
}