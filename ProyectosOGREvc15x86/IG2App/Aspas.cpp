#include "Aspas.h"
#include <OgreEntity.h>


Aspa::Aspa(Ogre::SceneManager* mSM, const std::string& name, bool adorn) {
	//mNode = mSM->getRootSceneNode()->createChildSceneNode(name);
	mNode = new Ogre::SceneNode(mSM);
	tableroNode = mNode->createChildSceneNode();

	Ogre::Entity* tablero = mSM->createEntity("cube.mesh");
	tableroNode->attachObject(tablero);

	tableroNode->setScale(10, 1.5, 0.3);
	if (adorn) {
		adornoNode = mNode->createChildSceneNode();

		Ogre::Entity* adorno = mSM->createEntity("Barrel.mesh");
		adornoNode->attachObject(adorno);

		adornoNode->setScale(10, 20, 10);

		adornoNode->setPosition(400, 0, 40);

		//Esto hace que no adquiera la rotación de su padre
		adornoNode->setInheritOrientation(false);
	}

}

Aspa::~Aspa()
{
	delete tableroNode;
	delete adornoNode;
	delete mNode;
}

void Aspa::setFather(Ogre::SceneNode* f)
{
	f->addChild(mNode);
}
