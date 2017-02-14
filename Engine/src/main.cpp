#include <iostream>

#include "../network/Client.hpp"
#include "../network/scene/SyncScene.hpp"

using namespace std;

/**
 * Main entry point for the Micro Engine.

 * Design goals:
 * - correct division of OpenGL into appropriate wrapper classes
 * - simple design
 * - each class should know as little as possible about other classes and non related parts of OpenGL
 * - the engine must allow different objects with different transforms, meshes, materials (shaders) etc
 * - consistent coding conventions
 * - reusable and extendable core set of classes which should require no modification
 *   (in other words it is possible to have a working "empty" example)
 *
 * All documentation is contained within the HEADER files, not the CPP files in possible.
 *
 */
int main()
{
    cout << "Starting Game" << endl;

	Client* client = new Client();
	thread tCon(&Client::Connect, client, (char*)"127.0.0.1", 8888);
	//client->Connect("127.0.0.1", 8888);

	SyncScene* syncScene = new SyncScene();
	syncScene->initialize();
	syncScene->run();
	tCon.join();

	//delete syncScene;
	delete client;

	cout << "Closing Game" << endl;
	cin.get();

    return 0;
}