#pragma once
#include "BrazoDron.h"


using ArmNodes = std::pair<Ogre::SceneNode*, BrazoDron*> ;

class Dron : public EntityIG
{
public:
	Dron(Ogre::SceneNode * mNode_, const int& numArms, const int& numAspas);
	~Dron();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	virtual void frameRendered(Ogre::FrameEvent const& evt);
	
	void EL_TRUCO(float const & degrees);

	void FICTICIO();

private:

	int numArms_, numAspas_;
	Ogre::SceneNode* sphere = nullptr;
	std::vector<ArmNodes> armNodes;

	bool isStopped;
	int clockWise;
	float gradesToAdd;
	unsigned int maxTime = 2000, timeLimit = 0;
	Ogre::Timer myTimer, myTimerStopped;

	Ogre::SceneNode* light = nullptr;
};

