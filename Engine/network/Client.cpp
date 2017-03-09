#include "../network/Client.hpp"

#include "../game/Level.hpp"
#include "../game/Enums.hpp"
#include "mge/auxiliary/AudioManager.h"

Client::Client()
{
	
}

Client::~Client()
{

}

int Client::Connect(const char* IP, int port)
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
		AudioManager::get()->PlaySoundW(SFX::connectionFailed1);
		PacketHelper::ErrorHandler();
		Disconnect();
		return 0;
	}

	AudioManager::get()->PlaySoundW(SFX::connectionSucces1);
	_connected = true;

	//Receive server NetCMD
	ReceiveResponse();

	//Start a thread for handling data
	thread receiveData(&Client::ReceiveData, this);
	receiveData.join();

	return 0;
}

int Client::Disconnect()
{
	cout << "Closing socket.." << endl;
	_playerId == Id::empty; //Reset player id
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

Id Client::GetId()
{
	return _playerId;
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
	case DataType::PLAYERDATA:
		PlayerData pData = *reinterpret_cast<PlayerData*>(buf);
		if (_playerId == pData.playerId || Level::getPlayer(pData.playerId) != NULL)
			return; //Data already exist
		cout << pData.playerId << " p ID" << endl;
		if (_playerId == Id::empty && pData.controlled)
		{
			_playerId = pData.playerId; //Assign player id
			cout << _playerId << " my ID" << endl;
		}
		Level::get()->AddSpawn(pData);
		break;
	case DataType::STARTDATA:
		StartData startData = *reinterpret_cast<StartData*>(buf);
		Level::get()->ResetStatues();
		Level::get()->Start(startData.start);
		break;
	case DataType::MOVEDATA:
		MoveData moveData = *reinterpret_cast<MoveData*>(buf);
		Level::get()->AddMove(moveData);
		break;
	case DataType::PICKUPDATA:
		PickupData pickupData = *reinterpret_cast<PickupData*>(buf);
		Level::get()->AddPickUp(pickupData);
		break;
	case DataType::TILEDATA:
		TileData tileData = *reinterpret_cast<TileData*>(buf);
		Level::get()->AddTile(tileData);
		break;
	case DataType::SCOREDATA:
		ScoreData scoreData = *reinterpret_cast<ScoreData*>(buf);
		Level::get()->SetScore(scoreData.playerId, scoreData.score);
		break;
	case DataType::EFFECTDATA:
		EffectData effectData = *reinterpret_cast<EffectData*>(buf);
		Level::get()->AddEffect(effectData);
		break;
	case DataType::STOREDATA:
		StoreData storeData = *reinterpret_cast<StoreData*>(buf);
		Level::get()->AddStore(storeData);
		break;
	case DataType::LEAVEDATA:
		LeaveData leaveData = *reinterpret_cast<LeaveData*>(buf);
		Level::get()->AddLeave(leaveData);
		break;
	case DataType::READYDATA:
		ReadyData readyData = *reinterpret_cast<ReadyData*>(buf);
		if (readyData.playerId == _playerId) return; //Ignore myself
		Level::get()->GetLobbyState()->UpdateVisual(readyData.playerId, readyData.ready);
		break;
	}
}