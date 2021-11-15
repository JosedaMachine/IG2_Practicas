#pragma once
#include "EntityIG.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include "AspasMolino.h"

class Avion: public EntityIG{
public:
	enum ACTION{
		OVERFLY,
		ORBITATE
	};
	Avion(Ogre::SceneNode * mNode_);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	virtual void frameRendered(Ogre::FrameEvent const& evt);

	void EL_TRUCO_Vertical(float const& degrees);

	void EL_TRUCO_Horizontal(float const& degrees);

	void setPlaneAction(ACTION act);

private:
	//No se como se hace, asique hay que preguntar el proximo dia
	Ogre::Entity* cuerpoAux;
	Ogre::Entity* alaDAux;
	Ogre::Entity* alaIAux;

	Ogre::SceneNode* cuerpoNode = nullptr;
	Ogre::SceneNode* alaINode = nullptr;
	Ogre::SceneNode* alaDNode = nullptr;
	Ogre::SceneNode* fernteNode = nullptr;
	Ogre::SceneNode* pilotoNode = nullptr;
	std::vector<AspasMolino*> heliceNodes;

	Ogre::SceneNode* light = nullptr;
					//Para pararlo con la R
	bool isStopped, manuallyStopped;
	int clockWise;
	float gradesToAdd;
	unsigned int maxTime = 2000, timeLimit = 0;
	ACTION planeAction;
	Ogre::Timer myTimer, myTimerStopped;

	void ToLeft();
	void ToRight();
	void Front();
	void NinjaPilot();
	void helices();
	void createLight();

	void restablishTextures();

	void orbitate();

	void overflyOgre();
	
protected:
	virtual void receiveEvent(Message mes,EntityIG* entidad);
};

