#pragma once
#include "BrazoDron.h"

using ArmNodes = std::pair<Ogre::SceneNode*, BrazoDron*> ;

class Dron : public EntityIG
{
public:
	Dron(Ogre::SceneNode * mNode_, const int& numArms, const int& numAspas);
	~Dron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	
	
private:

	int numArms_, numAspas_;
	Ogre::SceneNode* sphere = nullptr;
	std::vector<ArmNodes> armNodes;
};

