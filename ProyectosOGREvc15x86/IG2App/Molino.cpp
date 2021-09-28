#include "Molino.h"
#include <OgreEntity.h>

Molino::Molino(Ogre::SceneManager* man)
{
	mSM = man;
	mNode = mSM->getRootSceneNode()->createChildSceneNode();

	//Esfera
	esf = mNode->createChildSceneNode();

	Ogre::Entity* esfera = mSM->createEntity("sphere.mesh");
	esf->attachObject(esfera);

	esf->setScale(10, 10, 10);

	esf->setPosition(0, 800, 0);

	//Nodo rotatorio
	nodoRotation = esf->createChildSceneNode();

	nodoRotation->setPosition(0, 800, 0);
	//Aspas
	aspas = new AspasMolino(mSM, 12);
	aspas->setFather(nodoRotation);

	aspas->getMain()->setPosition(0, -800, 110);
	
	aspas->getMain()->scale(0.2, 0.2, 0.2);
	//Cilindro
	cil = nodoRotation->createChildSceneNode();

	Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
	cil->attachObject(cilindro);

	cil->setPosition(0, -950, 0);

	cil->setScale(40, 40, 40);

}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g || evt.keysym.sym == SDLK_c) {
		aspas->keyPressed(evt);
	}
	else if (evt.keysym.sym == SDLK_h) {
		nodoRotation->yaw(Ogre::Degree(2));
	}

	return true;
}
