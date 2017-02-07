#ifndef UNITYSCENE_H
#define UNITYSCENE_H

#include <mge/core/AbstractGame.hpp>

class DebugHud;

class UnityScene: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		UnityScene();
		virtual ~UnityScene();

        virtual void initialize();

	protected:
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();

	private:
		DebugHud* _hud;                   //hud display

        void _updateHud();

        UnityScene(const UnityScene&);
        UnityScene& operator=(const UnityScene&);
};

#endif // TERRAINSCENE_H
