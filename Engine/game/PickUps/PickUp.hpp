#ifndef PICKUP_H
#define PICKUP_H

#include "mge/core/GameObject.hpp"
#include "mge/materials/LitMaterial.hpp"

class PickUp : public GameObject
{
public:
	LitMaterial* _material;

	PickUp(std::string name);

	void getPickUp();
	void spawn();

private:
	float _minDelay;
	float _maxDelay;

};

#endif