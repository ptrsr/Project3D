#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <mge/core/AbstractGame.hpp>

#include "mge/core/GameObject.hpp"
#include "mge/scenes/menuStates/AbstactState.hpp"
class DebugHud;


class GameTimer
{
    //PUBLIC FUNCTIONS

	public:
		GameTimer();
		virtual ~GameTimer();

		virtual void _initializeScene();
		virtual void Update(float timeToUpdateWith);
		void setTimeLenght(float minutes);

	private:
		GameObject * placeToRenderText;
		int _counter = 0;
		void _updateTimer(float timeToUpdateWith);
		void createObject(char obj,int digid);
		GameObject* _firstDigid;
		GameObject* _doubleDots;
		GameObject* _secondDigid;
		GameObject* _thirdDigid;
		string _textToDislplay;
		float _minutes = 0;
		string copyForCompare;
		std::vector<GameObject*> objs;

		GameTimer(const GameTimer&);
		GameTimer& operator=(const GameTimer&);
};

#endif // TEXT_H
