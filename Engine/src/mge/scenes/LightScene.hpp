#ifndef LIGHTSCENE_H
#define LIGHTSCENE_H

#include <mge/core/AbstractGame.hpp>

class DebugHud;

class LightScene: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		LightScene();
		virtual ~LightScene();

        virtual void initialize();

	protected:
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();

	private:
		DebugHud* _hud;                   //hud display

        void _updateHud();

        LightScene(const LightScene&);
        LightScene& operator=(const LightScene&);
};

#endif // LIGHTSCENE_H
