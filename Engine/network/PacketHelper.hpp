#pragma once

#include <Windows.h>

#include "../network/DataType.hpp"

#include "../network/Data.hpp"
#include "../network/PlayerData.hpp"
#include "../network/TileData.hpp"
#include "../network/ScoreData.hpp"
#include "../network/TestData.hpp"

using namespace std;

class PacketHelper
{
public:
	static int Send(char* dataType, char* data, int dataLen, SOCKET client);
	static pair<DataType*, char*> Receive(SOCKET client);
private:
	static int SendData(char* buf, int len, SOCKET client);
	static int ReceiveData(char* buf, int len, SOCKET client);
	static int SizeOfData(DataType* type);
};