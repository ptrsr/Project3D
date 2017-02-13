#include "../network/PacketHelper.hpp"

int PacketHelper::Send(DataType dataType, char* data, SOCKET client)
{
	//Send DataType
	SendData((char*)&dataType, sizeof(DataType), client);
	//Send the actual data
	SendData(data, SizeOfData(dataType), client);

	return 0;
}

pair<DataType, char*> PacketHelper::Receive(char* buffer, SOCKET client)
{
	//Buffer
	char dataType[4];
	//Receive DataType
	ReceiveData(dataType, 4, client);

	DataType type = *reinterpret_cast<DataType*>(dataType);

	//Receive actual data using the buffer
	ReceiveData(buffer, SizeOfData(type), client);

	return make_pair(type, buffer);
}

int PacketHelper::SizeOfData(DataType type)
{
	switch (type)
	{
	case DataType::NETWORKCMD:
		return sizeof(NetWorkCommand);
	case DataType::TESTDATA:
		return sizeof(TestData);
	case DataType::PLAYERDATA:
		return sizeof(PlayerData);
	default:
		//cout << "ERROR: Could not match a DataType" << endl;
		break;
	}
}

int PacketHelper::SendData(char* buf, int len, SOCKET client)
{
	int dataLen = _WINSOCKAPI_::send(client, buf, len, 0); //Sends a char buffer to the client with a length and flag 0
	if (dataLen < 0)
	{
		cout << "ERROR: Failed to send data" << endl;
		return -1;
	}
	return dataLen;
}

int PacketHelper::ReceiveData(char* buf, int len, SOCKET client)
{
	int dataLen = _WINSOCKAPI_::recv(client, buf, len, 0); //Receive a char buffer from the client with a length and flag 0
	if (dataLen < 0)
	{
		//cout << "ERROR: Failed to receive data" << endl;
		return -1;
	}
	return dataLen;
}