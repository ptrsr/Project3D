#include "PickUp.hpp"
#include "mge/core/World.hpp"
#include "../Player.hpp"

PickUp::PickUp(std::string name) : GameObject(name)
{
	World::add(this);
}

void PickUp::spawn()
{

}