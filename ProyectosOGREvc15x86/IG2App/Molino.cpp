#include "Molino.h"
#include <OgreEntity.h>

Molino::Molino(Ogre::SceneManager* man)
{
	mSM = man;
	mNode = mSM->getRootSceneNode()->createChildSceneNode();

	aspas = new AspasMolino(mSM, 12);
	aspas->setFather(mNode);

	aspas->getMain()->setPosition(0, 1000, 550);
	
	cil = mNode->createChildSceneNode();

	Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
	cil->attachObject(cilindro);

	cil->setScale(200, 200, 200);

	esf = mNode->createChildSceneNode();

	Ogre::Entity* esfera = mSM->createEntity("sphere.mesh");
	esf->attachObject(esfera);


	esf->setScale(5, 5, 5);

	esf->setPosition(0, 800, 0);
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) {
		aspas->keyPressed(evt);
	}
	else if (evt.keysym.sym == SDLK_c) {
		
	}

	return true;
}
