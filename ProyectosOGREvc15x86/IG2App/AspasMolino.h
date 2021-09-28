#pragma once

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreInput.h>

#include "Aspas.h"

//#include <vector>

//#define const numAspas 12;

class AspasMolino : public OgreBites::InputListener {
public:
	AspasMolino(Ogre::SceneManager* mSM, const int& numAspas_ = 12, bool adornos = true);

	~AspasMolino();

	Ogre::SceneNode* getMain();

	bool keyPressed(const OgreBites::KeyboardEvent& evt);

	void setFather(Ogre::SceneNode* f);

private:
	Ogre::SceneManager* mSM = nullptr;
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* cilindroCentralNode = nullptr;
	Ogre::SceneNode* aspasNode = nullptr;

	int numAspas;
	std::vector<Aspa*> arrayAspas;
};

