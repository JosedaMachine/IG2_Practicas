#pragma once
#include "EntityIG.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include "AspasMolino.h"

class Avion: public EntityIG
{
public:
	Avion(Ogre::SceneNode * mNode_);


	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	virtual void frameRendered(Ogre::FrameEvent const& evt);

	void EL_TRUCO(float const& degrees);

private:

	Ogre::SceneNode* cuerpoNode = nullptr;
	Ogre::SceneNode* alaINode = nullptr;
	Ogre::SceneNode* alaDNode = nullptr;
	Ogre::SceneNode* fernteNode = nullptr;
	Ogre::SceneNode* pilotoNode = nullptr;
	std::vector<AspasMolino*> heliceNodes;

	Ogre::SceneNode* light = nullptr;

	bool isStopped;
	int clockWise;
	float gradesToAdd;
	unsigned int maxTime = 2000, timeLimit = 0;
	Ogre::Timer myTimer, myTimerStopped;

	//!? JEJE LES CAMBIE EL NOMBRE Y ENCIMA COMENTO EN MORADO PARA QUE TE JODA MAS
	void ToLeft();
	void ToRight();
	void Front();
	void NinjaPilot();
	void helices();
	void createLight();
};

