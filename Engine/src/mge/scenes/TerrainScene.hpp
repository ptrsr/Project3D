#ifndef TERRAINSCENE_H
#define TERRAINSCENE_H

#include <mge/core/AbstractGame.hpp>

class DebugHud;

class TerrainScene: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		TerrainScene();
		virtual ~TerrainScene();

        virtual void initialize();

	protected:
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();

	private:
		DebugHud* _hud;                   //hud display

        void _updateHud();

        TerrainScene(const TerrainScene&);
        TerrainScene& operator=(const TerrainScene&);
};

#endif // TERRAINSCENE_H
