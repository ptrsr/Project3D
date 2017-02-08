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
		AbstactState * _currentState;
        void _updateHud();
		void _changeState(int result);

		MenuScene(const MenuScene&);
		MenuScene& operator=(const MenuScene&);
};

#endif // LIGHTSCENE_H
