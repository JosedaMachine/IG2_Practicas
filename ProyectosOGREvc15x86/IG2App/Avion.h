#pragma once
#include "EntityIG.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreBillboardSet.h>
#include <OgreBillboard.h>

#include <OgreParticleSystem.h>

#include "AspasMolino.h"

class Avion: public EntityIG{
public:
	enum ACTION{
		OVERFLY,
		ORBITATE,
		NOTHING
	};
	Avion(Ogre::SceneNode * mNode_);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	virtual void frameRendered(Ogre::FrameEvent const& evt);

	void EL_TRUCO_Vertical(float const& degrees);

	void EL_TRUCO_Horizontal(float const& degrees);

	void setPlaneAction(ACTION act);

	void setParticleSys();

	void setFinalSceneConfig();
private:
	//No se como se hace, asique hay que preguntar el proximo dia
	Ogre::Entity* cuerpoAux,
				 * alaDAux,
				 * alaIAux;

	Ogre::SceneNode* cuerpoNode = nullptr,
					* alaINode = nullptr,
					* alaDNode = nullptr,
					* fernteNode = nullptr,
					* pilotoNode = nullptr;

	std::vector<AspasMolino*> heliceNodes;

	Ogre::ParticleSystem* pSys;
	Ogre::ParticleSystem* ex = nullptr;

	Ogre::SceneNode* light = nullptr;
					//Para pararlo con la R
	bool isStopped, manuallyStopped;
	int clockWise;
	float gradesToAdd;
	unsigned int maxTime = 2000, timeLimit = 0;
	ACTION planeAction;
	Ogre::Timer myTimer, myTimerStopped;
	Ogre::BillboardSet* points;

	void ToLeft();
	void ToRight();
	void Front();
	void NinjaPilot();
	void helices();
	void createLight();

	void createBillBoard();

	void restablishTextures();

	void orbitate();

	void overflyOgre();
	
protected:
	virtual void receiveEvent(Message mes,EntityIG* entidad);
};

