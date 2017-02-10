#include "../network/PacketHelper.hpp"

int PacketHelper::Send(char* dataType, char* data, int dataLen, SOCKET client)
{
	//Send DataType and it's size
	SendData(dataType, sizeof(DataType), client);
	//Send the actual data
	SendData(data, dataLen, client);

	return 0;
}

pair<DataType, char*> PacketHelper::Receive(SOCKET client)
{
	//Buffer
	char dataType[4];
	//Receive DataType
	ReceiveData(dataType, 4, client);

	DataType* type = reinterpret_cast<DataType*>(dataType);

	//Buffer
	char classData[256];
	//Receive actual data
	ReceiveData(classData, SizeOfData(type), client);

	return make_pair(*type, classData);
}

int PacketHelper::SizeOfData(DataType* type)
{
	switch (*type)
	{
	case DataType::TESTDATA:
		return sizeof(TestData);
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
		cout << "ERROR: Failed to receive data" << endl;
		return -1;
	}
	return dataLen;
}