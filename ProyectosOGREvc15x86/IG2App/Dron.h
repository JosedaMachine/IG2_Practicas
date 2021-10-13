#pragma once
#include "BrazoDron.h"

using ArmNodes = std::pair<Ogre::SceneNode*, BrazoDron*> ;

class Dron : public EntityIG
{
public:
	Dron(Ogre::SceneNode * mNode_, const int& numArms, const int& numAspas);
	~Dron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	Ogre::SceneNode* getMainNode() const { return mNode; }

	
private:

	int numArms_, numAspas_;
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* sphere = nullptr;
	Ogre::SceneManager* mSM = nullptr;
	std::vector<ArmNodes> armNodes;

};

