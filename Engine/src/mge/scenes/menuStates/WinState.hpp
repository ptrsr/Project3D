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
		std::vector<GameObject*> _numbers;
		GameObject* _plane;
		int _counter = 0;
		int _waitTime = 500;
		bool _finished = false;
		bool _spawned = false;


		void spawnRanking();
		GameObject* getStatue(int playerId);

		Id GetHighestScore(float* scores);
		void AddNumberObj(Id playerId, int place);
		Mesh* GetNumberMesh(int place);

		WinState(const WinState&);
		WinState& operator=(const WinState&);
};

#endif // LIGHTSCENE_H
