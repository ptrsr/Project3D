#pragma once

#include <Windows.h>

#include "../network/NetworkCommand.hpp"
#include "../network/packets/DataType.hpp"

#include "../network/packets/TimeData.hpp"
#include "../network/packets/StartData.hpp"
#include "../network/packets/PlayerData.hpp"
#include "../network/packets/MoveData.hpp"
#include "../network/packets/TileData.hpp"
#include "../network/packets/ScoreData.hpp"
#include "../network/packets/TestData.hpp"
#include "../network/packets/PickupData.hpp"
#include "../network/packets/EffectData.hpp"
#include "../network/packets/StoreData.hpp"
#include "../network/packets/UseData.hpp"

using namespace std;

class PacketHelper
{
public:
	static int Send(DataType dataType, char* data, SOCKET client);
	static pair<DataType, char*> Receive(char* buffer, SOCKET client);
	static bool Connected(SOCKET client);
	static void ErrorHandler();
private:
	static int SendData(char* buf, int len, SOCKET client);
	static int ReceiveData(char* buf, int len, SOCKET client);
	static int SizeOfData(DataType type);
};