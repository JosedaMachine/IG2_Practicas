#pragma once
#include "EntityIG.h"
#include <iostream>
#include <OgreTimer.h>
#include <OgreEntity.h>

using namespace Ogre;

class Sinbad : public EntityIG
{
public:
	Sinbad(Ogre::SceneNode* _node);
	virtual ~Sinbad();
	void arma();

	void setRoute(Vector3 const& intial, Vector3 const& final);

private:
	// Heredado vía EntityIG
	virtual void frameRendered(Ogre::FrameEvent const& evt) override;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	
	void EL_TRUCO(float const& degrees);
	void getAnimationNames(Ogre::Entity* ent);
	void gira();

	void routeAnim();

	void arma(bool has);
	void cambiaEspada();

	bool isStopped, hasSwords, isDancing;

	Vector3 initalPoint, finalPoint;
	Ogre::Entity* cuerpo, *swordL, * swordR;
	Ogre::Timer myTimer, myTimerStopped;
	Ogre::AnimationState* runBase = nullptr, * runTop = nullptr, * dance = nullptr, *route = nullptr;

	Ogre::SceneNode* animationNode; //Para poder escalar a SinBad independientemente de las animaciones

	int clockWise;
	float gradesToAdd;
	unsigned int maxTime = 2000, timeLimit = 0;
};

