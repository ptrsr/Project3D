#include "../network/Client.hpp"

#include "../network/scene/SyncScene.hpp"

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
	WSAStartup(MAKEWORD(2, 2), &_data); //Initialize our socket on version 2.2 and save it to data
	_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Set socket type IPv4 and set stream, TCP protocol

	//Time-out struct
	timeval tv;
	tv.tv_sec = _timeOut;

	//Apply time-out to socket
	setsockopt(_sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof(tv));
	setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));

	if (_sock == INVALID_SOCKET)
	{
		PacketHelper::ErrorHandler();
		WSACleanup();
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
		PacketHelper::ErrorHandler();
		Disconnect();
		return 0;
	}

	_connected = true;

	//Receive server NetCMD
	ReceiveResponse();

	DataType dataType = DataType::PLAYERDATA;
	DataType dataType2 = DataType::TESTDATA;

	//Start a thread for handling data
	thread receiveData(&Client::ReceiveData, this);

	if (!_connected)
	{
		receiveData.join();
		return 0;
	}

	TestData testData;
	testData.t = 512;
	testData.r = 0.15f;
	testData.g = 0.30f;
	testData.b = 0.60f;
	testData.a = 0.075f;
	string input = "Testing a very long message to see if it receives correctly on the other side";
	strcpy(testData.input, input.c_str());

	TestData testData2;
	testData2.t = 0;
	testData2.r = 0;
	testData2.g = 0;
	testData2.b = 0;
	testData2.a = 0;
	string input2 = "Here is another string";
	strcpy(testData2.input, input2.c_str());

	PlayerData playerData;
	playerData.direction = Dir::up;
	PlayerData playerData2;
	playerData2.direction = Dir::down;
	PlayerData playerData3;
	playerData3.direction = Dir::left;
	PlayerData playerData4;
	playerData4.direction = Dir::right;

	PacketHelper::Send(dataType2, (char*)&testData, _sock);
	PacketHelper::Send(dataType2, (char*)&testData2, _sock);
	PacketHelper::Send(dataType, (char*)&playerData, _sock);
	PacketHelper::Send(dataType, (char*)&playerData2, _sock);
	PacketHelper::Send(dataType, (char*)&playerData3, _sock);
	PacketHelper::Send(dataType, (char*)&playerData4, _sock);

	receiveData.join();

	return 0;
}

int Client::Disconnect()
{
	cout << "Closing socket.." << endl;
	_connected = false; //Stop the data loop
	closesocket(_sock); //Close our socket
	WSACleanup(); //Clean up everything
	cout << "Socked closed" << endl;
	return 1;
}

void Client::Send(DataType type, char* data)
{
	PacketHelper::Send(type, data, _sock);
}

void Client::ReceiveResponse()
{
	char buffer[4];
	pair<DataType, char*> data = PacketHelper::Receive(buffer, _sock);
	HandlePacket(data.first, data.second);
}

void Client::ReceiveData()
{
	while (_connected)
	{
		//Check if we are still connected
		if (!PacketHelper::Connected(_sock))
		{
			Disconnect();
			break;
		}

		char buf[256];
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
		cout << testData.pX << " " << testData.pY << " " << testData.pZ << " " << testData.rX << " " << testData.rY << " " << testData.rZ << endl;

		SyncScene::instance->gCube->setLocalPosition(glm::vec3(testData.pX, testData.pY, testData.pZ));
		break;
	case DataType::PLAYERDATA:
		PlayerData playerData = *reinterpret_cast<PlayerData*>(buf);
		switch (playerData.direction)
		{
		case Dir::up:
			cout << "up" << endl;
			break;
		case Dir::down:
			cout << "down" << endl;
			break;
		case Dir::left:
			cout << "left" << endl;
			break;
		case Dir::right:
			cout << "right" << endl;
			break;
		}
	break;
	}
}