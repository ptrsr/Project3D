#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include <mge/core/AbstractGame.hpp>

#include "mge/core/GameObject.hpp"
#include "mge/scenes/menuStates/AbstactState.hpp"
class DebugHud;

class CreditsState : public AbstactState
{
    //PUBLIC FUNCTIONS

	public:
		CreditsState();
		virtual ~CreditsState();

		virtual void _initializeScene();
		virtual void Update();
		virtual int CheckSelection();
		virtual GameObject* getPlane();
		virtual void deleteScene();

	private:
		GameObject* _writingStone;
		GameObject* _selectableObj;
		GameObject* _plane;
		int _counter = 0;
		void _updateColor();
		void _clearObjectColor();

		bool _isKeyPress = true;
		int _delay = 15;
		int _delayCounter = 0;

		CreditsState(const CreditsState&);
		CreditsState& operator=(const CreditsState&);
};

#endif // LIGHTSCENE_H
