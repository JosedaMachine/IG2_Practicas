#pragma once
#include "EntityIG.h"
class Avion: public EntityIG
{
	Avion(Ogre::SceneManager* mSM_, const int& numArms, const int& numAspas, Ogre::SceneNode* father = nullptr);
};

