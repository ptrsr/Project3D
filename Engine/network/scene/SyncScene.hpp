#pragma once

#include <mge/core/AbstractGame.hpp>
#include "mge/core/GameObject.hpp"

#include "../network/Client.hpp"

class SyncScene : public AbstractGame
{
	//PUBLIC FUNCTIONS

public:
	SyncScene();
	virtual ~SyncScene();

	virtual void initialize();

	static SyncScene* instance;

	GameObject* gCube;

	Client* client;
protected:
	virtual void _initializeScene();

	//override render to render the hud as well.
	virtual void _render();

private:
	void _updateHud();

	SyncScene(const SyncScene&);
	SyncScene& operator=(const SyncScene&);
};