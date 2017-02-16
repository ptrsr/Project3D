#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <mge/core/AbstractGame.hpp>
#include "../game/Level.hpp"

class DebugHud;

class LevelScene: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		LevelScene();
		virtual ~LevelScene();

        virtual void initialize();

	protected:
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();

	private:
		DebugHud* _hud;                   //hud display
		Level* _level;

        void _updateHud();

        LevelScene(const LevelScene&);
        LevelScene& operator=(const LevelScene&);
};

#endif // LIGHTSCENE_H
