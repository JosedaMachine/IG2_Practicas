#include "Aspas.h"

Aspa::Aspa(Ogre::SceneManager* mSM, const std::string& name) {
	mNode = mSM->getRootSceneNode()->createChildSceneNode(name);
	tableroNode = mNode->createChildSceneNode();

	Ogre::Entity* tablero = mSM->createEntity("cube.mesh");
	tableroNode->attachObject(tablero);

	tableroNode->setScale(10, 1.5, 0.3);

	adornoNode = mNode->createChildSceneNode();

	Ogre::Entity* adorno = mSM->createEntity("Barrel.mesh");
	adornoNode->attachObject(adorno);

	adornoNode->setScale(10, 20, 10);

	adornoNode->setPosition(400, 0, 40);
}

Aspa::~Aspa()
{
	delete tableroNode;
	delete adornoNode;
	delete mNode;
}