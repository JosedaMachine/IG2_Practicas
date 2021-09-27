#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include "AspasMolino.h"

#pragma once
class Molino
{
public:
	Molino(Ogre::SceneManager*mSM);
	~Molino();

	void rotateBlades(const float& degrees);

private:
	Ogre::SceneManager* mSM = nullptr;
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* tap, *body;
	AspasMolino* blades = nullptr;
};


