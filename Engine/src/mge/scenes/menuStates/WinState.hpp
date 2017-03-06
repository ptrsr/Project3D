#ifndef WINSTATE_H
#define WINSTATE_H

#include <mge/core/AbstractGame.hpp>

#include "mge/core/GameObject.hpp"
#include "mge/scenes/menuStates/AbstactState.hpp"
class DebugHud;

class WinState : public AbstactState
{
    //PUBLIC FUNCTIONS

	public:
		WinState();
		virtual ~WinState();

		virtual void _initializeScene();
		virtual void Update();
		virtual int CheckSelection();
		virtual GameObject* getPlane();
		virtual void deleteScene();

	private:

		Mesh * _oneBig;
		Mesh * _twoBig;
		Mesh * _threeBig;
		Mesh * _fourBig;
		GameObject * _firstPos;
		GameObject * _secondPos;
		GameObject * _thirdPos;
		GameObject * _forthPos;
		GameObject* _plane;
		int _counter = 0;
		int _waitTime = 500;
		bool _finished = false;
		bool _spawned = false;


		void spawnRanking();
		glm::vec3 getStatue(int playerId);

		WinState(const WinState&);
		WinState& operator=(const WinState&);
};

#endif // LIGHTSCENE_H
