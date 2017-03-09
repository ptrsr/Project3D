#ifndef LOBBYSTATE_H
#define LOBBYSTATE_H

#include <mge/core/AbstractGame.hpp>

#include "mge/core/GameObject.hpp"
#include "mge/scenes/menuStates/AbstactState.hpp"
#include "mge/materials/StatueMaterial.hpp"
#include "../game/Player.hpp"
class DebugHud;

class LobbyState : public AbstactState
{
    //PUBLIC FUNCTIONS

	public:
		LobbyState(Player* forPlayer);
		virtual ~LobbyState();

		virtual void _initializeScene();
		virtual void Update();
		virtual int CheckSelection();
		virtual GameObject* getPlane();
		virtual void deleteScene();
		bool isReady();
		void setReady(bool value);
		GameObject* GetStatue(Id playerId);
		void UpdateVisual(Id playerId, bool value);

	private:
		Player* _player;
		StatueMaterial* _playerMaterial;
		GameObject* _playerStatue;

		int _counter = 0;
		bool _ready = false;

		bool _isKeyPress = true;
		int _delay = 15;
		int _delayCounter = 0;

		LobbyState(const LobbyState&);
		LobbyState& operator=(const LobbyState&);
};

#endif // LOBBYSTATE_H
