#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <mge/core/AbstractGame.hpp>

#include "mge/core/GameObject.hpp"

#include "mge/scenes/menuStates/AbstactState.hpp"
class DebugHud;

class MenuScene : public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		MenuScene();
		virtual ~MenuScene();

        virtual void initialize();

	protected:
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();

	private:
		DebugHud* _hud;
		AbstactState * _startState;
		AbstactState * _joinState;
		AbstactState * _creditsState;
		AbstactState* _newState = nullptr;
		int _currentState = -1;
		int _nextState = -1;
		bool _cameraStateChanged = false;
        void _updateHud();
		void _changeState(int result);
		void _changeCameraState(AbstactState* state);
		void _deleteScene();

		MenuScene(const MenuScene&);
		MenuScene& operator=(const MenuScene&);
};

#endif // LIGHTSCENE_H
