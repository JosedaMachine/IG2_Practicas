#pragma once
#include "EntityIG.h"
#include "RotorDron.h"

class BrazoDron : public EntityIG
{
public:
	BrazoDron(Ogre::SceneNode* mNode_, const bool& clockWise, const int& numAspas = 6/*, Ogre::SceneNode* parent = nullptr*/);
	~BrazoDron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	void rotateAspas();

private:
	/*Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneManager* mSM = nullptr;*/

	Ogre::SceneNode* rotorNode = nullptr;
	Ogre::SceneNode* cilindro = nullptr;
	RotorDron* rotor = nullptr;
	int numAspas_;
};

