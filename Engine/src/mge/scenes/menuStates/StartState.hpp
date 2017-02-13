#ifndef STARTSTATE_H
#define STARTSTATE_H

#include <mge/core/AbstractGame.hpp>

#include "mge/core/GameObject.hpp"
#include "mge/scenes/menuStates/AbstactState.hpp"
class DebugHud;

class StartState : public AbstactState
{
    //PUBLIC FUNCTIONS

	public:
		StartState();
		virtual ~StartState();

		virtual void _initializeScene();
		virtual void Update();
		virtual int CheckSelection();
		virtual GameObject* getPlane();
		virtual void deleteScene();

	private:
		GameObject* _selectableObjs[4];
		GameObject* _plane;
		int _counter = 0;
		void _updateColor();
		void _clearObjectColor();

		bool _isKeyPress = true;
		int _delay = 15;
		int _delayCounter = 0;

		StartState(const StartState&);
		StartState& operator=(const StartState&);
};

#endif // LIGHTSCENE_H
