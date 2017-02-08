#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

#include <mge/core/AbstractGame.hpp>

#include "mge/core/GameObject.hpp"
class DebugHud;

class AbstactState : AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		AbstactState();
		virtual ~AbstactState();
		virtual void _initializeScene() = 0;
		virtual void Update() = 0;
		virtual int CheckSelection() = 0;
		


		AbstactState(const AbstactState&);
		AbstactState& operator=(const AbstactState&);
};

#endif // LIGHTSCENE_H
