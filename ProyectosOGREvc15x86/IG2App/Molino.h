#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include "AspasMolino.h"
#include "EntityIG.h"

#pragma once
class Molino : public EntityIG
{
public:
	Molino(Ogre::SceneNode * mNode_);
	~Molino();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	void rotar1(const float& angle);
	void rotar2(const float& angle);
	
private:
	Ogre::SceneManager* mSM = nullptr;
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* tap, *body, *aspas;
	AspasMolino* blades = nullptr;

	int radioAspasMolino;
};


