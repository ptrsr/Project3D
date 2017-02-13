#include "../network/Client.hpp"

#include <thread>
#include <sstream>

#include "../network/PacketHelper.hpp"

#include "mge/core/GameObject.hpp"

Client::Client()
{

}

Client::~Client()
{

}

int Client::Connect(char* IP, int port)
{
	cout << "Setting up client.." << endl;
	cout << "Creating socket.." << endl;
	WSAStartup(MAKEWORD(2, 2), &_data); //Initialize our socket on version 2.2 and saveit to data
	_sock = socket(AF_INET, SOCK_STREAM, 0); //Set socket type IPv4 and set stream, protocol 0 = UDP

	if (_sock == INVALID_SOCKET)
	{
		cout << "ERROR: Invalid socket" << endl;
		return 1;
	}

	cout << "Socket creation succesful" << endl;

	cout << "Assigning socket info" << endl;

	_iSock.sin_family = AF_INET; //Assign socket type to IPv4
	_iSock.sin_addr.s_addr = inet_addr(IP); //Set the IP to the server
	_iSock.sin_port = htons(port); //Sets the port to the server

	cout << "Assigned socket info" << endl;

	cout << "Connecting to " << IP << ":" << port << endl;
	int connection = connect(_sock, (struct sockaddr*)&_iSock, sizeof(_iSock)); //Connect to the server given the info from out socket and size of our socket
	if (connection != 0)
	{
		cout << "ERROR: Failed to connect" << endl;
		return 0;
	}

	_connected = true;

	GameObject* obj = new GameObject("Test", glm::vec3(5, 1, 7));

	DataType dataType = DataType::PLAYERDATA;
	DataType dataType2 = DataType::TESTDATA;

	//Start a thread for handling data
	thread receiveData(&Client::ReceiveData, this);

	TestData testData;
	testData.t = 512;
	testData.r = 0.15f;
	testData.g = 0.30f;
	testData.b = 0.60f;
	testData.a = 0.075f;

	PlayerData playerData;
	playerData.direction = Direction::up;
	PlayerData playerData2;
	playerData2.direction = Direction::down;
	PlayerData playerData3;
	playerData3.direction = Direction::left;
	PlayerData playerData4;
	playerData4.direction = Direction::right;

	PacketHelper::Send(dataType2, (char*)&testData, _sock);
	PacketHelper::Send(dataType, (char*)&playerData, _sock);
	PacketHelper::Send(dataType, (char*)&playerData2, _sock);
	PacketHelper::Send(dataType, (char*)&playerData3, _sock);
	PacketHelper::Send(dataType, (char*)&playerData4, _sock);

	receiveData.join();

	return 0;
}

void Client::ReceiveData()
{
	while (_connected)
	{
		char buf[50];
		pair<DataType, char*> data = PacketHelper::Receive(buf, _sock);
		HandlePacket(data.first, data.second);
	}
}

void Client::HandlePacket(DataType type, char* buf)
{
	switch (type)
	{
	case DataType::NETWORKCMD:
	{
		NetWorkCommand netCode = *reinterpret_cast<NetWorkCommand*>(buf);
		switch (netCode)
		{
		case CONNECTION_ACCEPTED:
			cout << "Succesfully connected" << endl;
			break;
		case SERVER_FULL:
			cout << "ERROR: Server is full" << endl;
			Disconnect();
			break;
		}
	}
		break;
	case DataType::TESTDATA:
		TestData testData = *reinterpret_cast<TestData*>(buf);
		cout << testData.t << " " << testData.r << " " << testData.g << " " << testData.b << " " << testData.a << endl;
		break;
	case DataType::PLAYERDATA:
	{
		PlayerData playerData = *reinterpret_cast<PlayerData*>(buf);
		switch (playerData.direction)
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

int Client::Disconnect()
{
	cout << "Disconnecting.." << endl;
	_connected = false; //Stop the data loop
	closesocket(_sock); //Close our socket
	WSACleanup(); //Clean up everything
	cout << "Disconnected" << endl;
	return 1;
}