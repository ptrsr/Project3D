#ifndef OBJECTVIEWER_H
#define OBJECTVIEWER_H

#include <mge/core/AbstractGame.hpp>

class DebugHud;

class ObjectViewer: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		ObjectViewer();
		virtual ~ObjectViewer();

        virtual void initialize();

	protected:
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();

	private:
		DebugHud* _hud;                   //hud display

        void _updateHud();

        ObjectViewer(const ObjectViewer&);
        ObjectViewer& operator=(const ObjectViewer&);
};

#endif // TERRAINSCENE_H
