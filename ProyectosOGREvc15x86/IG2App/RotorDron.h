#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>

#include "Aspas.h"
#include "AspasMolino.h"

#include "EntityIG.h"

class RotorDron : public EntityIG {

public:
	RotorDron(Ogre::SceneManager* mSM, const int& numHelices = 6, Ogre::SceneNode* parent = nullptr);

	~RotorDron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* helicesNode = nullptr;
	Ogre::SceneNode* esferaNode = nullptr;

	int numHelices_;
	Helices* aspasM = nullptr;
};

