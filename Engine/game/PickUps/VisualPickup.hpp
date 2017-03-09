#ifndef VISUALPICKUP_H
#define VISUALPICKUP_H

#include "mge/core/GameObject.hpp"
#include "mge/core/Texture.hpp"

class VisualPickup : public GameObject
{
public:
	VisualPickup();
	void visualizeSpeed();
	void visualizeSplash();
	void clear();
private:
	GameObject * _objToVisualiseOn;
	Texture* _speedTexture;
	Texture* _splashTexture;
	Texture* _emptyTexture;
};
#endif