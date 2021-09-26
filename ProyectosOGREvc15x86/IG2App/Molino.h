#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreInput.h>

#include "AspasMolino.h"
class Molino : public OgreBites::InputListener
{
public:
	Molino(Ogre::SceneManager* man);


private:
	Ogre::SceneManager* mSM = nullptr;

	Ogre::SceneNode* mNode = nullptr;

	AspasMolino* aspas = nullptr;

	Ogre::SceneNode* esf = nullptr;
	Ogre::SceneNode* cil = nullptr;
};

