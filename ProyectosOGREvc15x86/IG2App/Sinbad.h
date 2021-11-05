#pragma once
#include "EntityIG.h"
#include <iostream>
#include <OgreTimer.h>
#include <OgreEntity.h>

class Sinbad : public EntityIG
{
public:
	Sinbad(Ogre::SceneNode* _node);
	virtual ~Sinbad();

private:
	// Heredado vía EntityIG
	virtual void frameRendered(Ogre::FrameEvent const& evt) override;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	
	void EL_TRUCO(float const& degrees);
	void getAnimationNames(Ogre::Entity* ent);
	void gira();

	void arma(bool has);
	void arma();
	void cambiaEspada();

	bool isStopped, hasSwords, isDancing;

	Ogre::Entity* cuerpo, *swordL, * swordR;
	Ogre::Timer myTimer, myTimerStopped;
	Ogre::AnimationState* runBase = nullptr, *runTop = nullptr, *dance = nullptr;
	int clockWise;
	float gradesToAdd;
	unsigned int maxTime = 2000, timeLimit = 0;
};

