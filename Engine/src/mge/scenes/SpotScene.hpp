#ifndef SPOTSCENE_H
#define SPOTSCENE_H

#include <mge/core/AbstractGame.hpp>

class DebugHud;

class SpotScene: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		SpotScene();
		virtual ~SpotScene();

        virtual void initialize();

	protected:
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();

	private:
		DebugHud* _hud;                   //hud display

        void _updateHud();

        SpotScene(const SpotScene&);
        SpotScene& operator=(const SpotScene&);
};

#endif // LIGHTSCENE_H
