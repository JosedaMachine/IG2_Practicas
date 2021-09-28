#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreInput.h>

#include "AspasMolino.h";

class RotorDron : public OgreBites::InputListener
{
public:
	RotorDron(Ogre::SceneManager* man);

	~RotorDron();

	bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:
	AspasMolino* aspasMol = nullptr;

	Ogre::SceneNode* esf = nullptr;
	Ogre::SceneNode* mNode = nullptr;

	Ogre::SceneManager* mSM = nullptr;
};

