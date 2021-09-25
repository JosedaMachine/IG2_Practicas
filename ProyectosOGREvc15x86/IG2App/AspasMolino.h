#pragma once

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include "Aspas.h"

//#include <vector>

//#define const numAspas 12;

class AspasMolino {
public:
	AspasMolino(Ogre::SceneManager* mSM, const int& numAspas_ = 12);

	~AspasMolino();

	Ogre::SceneNode* getMainNode() const { return mNode; }

private:
	Ogre::SceneManager* mSM = nullptr;
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* cilindroCentralNode = nullptr;
	Ogre::SceneNode* aspasNode = nullptr;

	int numAspas;
	std::vector<Aspa*> arrayAspas;
};

