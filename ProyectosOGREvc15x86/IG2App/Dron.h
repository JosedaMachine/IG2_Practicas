#pragma once
#include "BrazoDron.h"

using ArmNodes = std::pair<Ogre::SceneNode*, BrazoDron*> ;

class Dron : public EntityIG
{
public:
	Dron(Ogre::SceneManager* mSM_, const int& numArms, const int& numAspas);
	~Dron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:

	int numArms_, numAspas_;
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* sphere = nullptr;
	Ogre::SceneManager* mSM = nullptr;
	std::vector<ArmNodes> armNodes;

};

