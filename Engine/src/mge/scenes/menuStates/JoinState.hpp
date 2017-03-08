#ifndef JOINSTATE_H
#define JOINSTATE_H

#include <mge/core/AbstractGame.hpp>

#include "mge/core/GameObject.hpp"
#include "mge/scenes/menuStates/AbstactState.hpp"
#include "mge/auxiliary/Text.hpp"
class DebugHud;

class JoinState : public AbstactState
{
    //PUBLIC FUNCTIONS

	public:
		JoinState();
		virtual ~JoinState();

		virtual void _initializeScene();
		virtual void Update();
		virtual int CheckSelection();
		virtual GameObject* getPlane();
		virtual void deleteScene();

	private:
		GameObject* _back;
		GameObject* _plane;
		GameObject* _enterIp;
		Text * _text;
		int _counter = 0;
		void _updateColor();
		void _clearObjectColor();

		bool _isKeyPress = true;
		int _delay = 15;
		int _delayCounter = 0;

		JoinState(const JoinState&);
		JoinState& operator=(const JoinState&);
};

#endif // LIGHTSCENE_H
