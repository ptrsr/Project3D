#include "../network/PacketHelper.hpp"

int PacketHelper::Send(char* buf, int len, SOCKET client)
{
	return 0;
}

pair<DataType*, char*> PacketHelper::Receive(SOCKET client)
{
	//Receive classifier
	char data1[4]; //Buffer
	ReceiveData(data1, 4, client);

	DataType* type = reinterpret_cast<DataType*>(data1);

	//Receive actual TestData
	char data2[256];
	ReceiveData(data2, SizeOfData(type), client);

	return make_pair(type, data2);
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