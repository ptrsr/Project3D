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

bool PacketHelper::Connected(SOCKET client)
{
	char buf;
	int err = recv(client, &buf, 1, MSG_PEEK);
	if (err == SOCKET_ERROR)
	{
		ErrorHandler();
		return false;
	}
	return true;
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
		cout << "ERROR: Could not match a DataType" << endl;
		break;
	}
}

int PacketHelper::SendData(char* buf, int len, SOCKET client)
{
	int dataLen = _WINSOCKAPI_::send(client, buf, len, 0); //Sends a char buffer to the client with a length and flag 0
	if (dataLen < 0)
	{
		ErrorHandler();
		return -1;
	}
	return dataLen;
}

int PacketHelper::ReceiveData(char* buf, int len, SOCKET client)
{
	int dataLen = _WINSOCKAPI_::recv(client, buf, len, 0); //Receive a char buffer from the client with a length and flag 0
	if (dataLen < 0)
	{
		ErrorHandler();
		return -1;
	}
	return dataLen;
}

void PacketHelper::ErrorHandler()
{
	int wsaErr = WSAGetLastError();

	switch (wsaErr)
	{
	case WSAEWOULDBLOCK:
		cout << "ERROR: Resource temporary unavailable : " << wsaErr << endl;
		break;
	case WSAEFAULT:
		cout << "ERROR: Bad address : " << wsaErr << endl;
		break;
	case WSAENOTSOCK:
		cout << "ERROR: Socket operation on nonsocket : " << wsaErr << endl;
		break;
	case WSAEMSGSIZE:
		cout << "ERROR: Message too long : " << wsaErr << endl;
		break;
	case WSAEPROTONOSUPPORT:
		cout << "ERROR: Protocol not supported : " << wsaErr << endl;
		break;
	case WSAESOCKTNOSUPPORT:
		cout << "ERROR: Socket type not found : " << wsaErr << endl;
		break;
	case WSAEOPNOTSUPP:
		cout << "ERROR: Operation not supported : " << wsaErr << endl;
		break;
	case WSAEPFNOSUPPORT:
		cout << "ERROR: Protocol family not supported : " << wsaErr << endl;
		break;
	case WSAEAFNOSUPPORT:
		cout << "ERROR: Address family not supported by protocol family : " << wsaErr << endl;
		break;
	case WSAEADDRINUSE:
		cout << "ERROR: Address already in use : " << wsaErr << endl;
		break;
	case WSAEADDRNOTAVAIL:
		cout << "ERROR: Cannot assign requested address : " << wsaErr << endl;
		break;
	case WSAENETDOWN:
		cout << "ERROR: Network is down : " << wsaErr << endl;
		break;
	case WSAENETUNREACH:
		cout << "ERROR: Network is unreachable : " << wsaErr << endl;
		break;
	case WSAENETRESET:
		cout << "ERROR: Network dropped on reset : " << wsaErr << endl;
		break;
	case WSAECONNABORTED:
		cout << "ERROR: Connection aborted : " << wsaErr << endl;
		break;
	case WSAECONNRESET:
		cout << "ERROR: Connection lost : " << wsaErr << endl;
		break;
	case WSAENOBUFS:
		cout << "ERROR: No buffer space availabe : " << wsaErr << endl;
		break;
	case WSAEISCONN:
		cout << "ERROR: Socket is already connected : " << wsaErr << endl;
		break;
	case WSAESHUTDOWN:
		cout << "ERROR: Cannot send after socket shutdown : " << wsaErr << endl;
		break;
	case WSAETIMEDOUT:
		cout << "ERROR: Connection timed out : " << wsaErr << endl;
		break;
	case WSAECONNREFUSED:
		cout << "ERROR: Connection refused : " << wsaErr << endl;
		break;
	case WSANOTINITIALISED:
		cout << "ERROR: Successful WSAStartup not yet performed : " << wsaErr << endl;
		break;
	}
}