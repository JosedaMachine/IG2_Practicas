#pragma once
#include "EntityIG.h"
#include "RotorDron.h"

class BrazoDron : public EntityIG
{
public:
	BrazoDron(Ogre::SceneManager* mSM_, const int& numAspas = 6);
	~BrazoDron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneManager* mSM = nullptr;

	Ogre::SceneNode* rotorNode = nullptr;
	Ogre::SceneNode* cilindro = nullptr;
	RotorDron* rotor = nullptr;
	int numAspas_;
};

