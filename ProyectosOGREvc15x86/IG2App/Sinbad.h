#pragma once
#include "EntityIG.h"
#include <iostream>
#include <OgreTimer.h>
#include <OgreEntity.h>

class Sinbad : public EntityIG
{
public:
	Sinbad(Ogre::SceneNode* _node);
	~Sinbad();

private:
	bool isStopped;
	Ogre::Timer myTimer, myTimerStopped;
	int clockWise;
	float gradesToAdd;
	unsigned int maxTime = 2000, timeLimit = 0;

	Ogre::AnimationState* runBase = nullptr, *runTop = nullptr, *dance = nullptr;
	Ogre::Entity* cuerpo;
	void getAnimationNames(Ogre::Entity* ent);
	// Heredado vía EntityIG
	virtual void frameRendered(Ogre::FrameEvent const& evt) override;

	void gira();

	void EL_TRUCO(float const& degrees);
};

