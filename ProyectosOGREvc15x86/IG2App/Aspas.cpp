#include "Aspas.h"

Aspa::Aspa(Ogre::SceneManager* mSM, const std::string& name, Ogre::SceneNode* nodeParent, bool showOrnament) {
	
	showOrnament_ = showOrnament;

	if (!nodeParent)
		mNode = mSM->getRootSceneNode()->createChildSceneNode(name);
	else mNode = nodeParent->createChildSceneNode(name);;

	tableroNode = mNode->createChildSceneNode();

	Ogre::Entity* tablero = mSM->createEntity("cube.mesh");
	tableroNode->attachObject(tablero);

	float scaleX = 10;
	tableroNode->setScale(scaleX, 1.5, 0.3);

	if (showOrnament) {
		adornoNode = mNode->createChildSceneNode();
		Ogre::Entity* adorno = mSM->createEntity("Barrel.mesh");
		adornoNode->attachObject(adorno);
		adornoNode->setScale(10, 20, 10);
		adornoNode->setPosition((scaleX*900)/20, 0, 40);
	}
}

Aspa::~Aspa() {
	delete tableroNode;
	delete adornoNode;
	delete mNode;
}