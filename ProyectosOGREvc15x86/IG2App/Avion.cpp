#include "Avion.h"


Avion::Avion(Ogre::SceneManager* mSM_, Ogre::SceneNode* father): mSM(mSM_) {
	if (!father)mNode = mSM->getRootSceneNode()->createChildSceneNode();
	else mNode = father->createChildSceneNode();

	cuerpoNode = mNode->createChildSceneNode();
	Ogre::Entity* cuerpo = mSM->createEntity("sphere.mesh");
	cuerpoNode->attachObject(cuerpo);

	alaIzquierda();

	alaDerecha();

	frente();

	pilotoNinja();

	helices();
}

void Avion::helices()
{
	AspasMolino* a1 = new AspasMolino(mSM, false, 6, mNode);
	a1->getMainNode()->scale(0.15, 0.15, 0.15);
	a1->getMainNode()->translate(Ogre::Vector3(300, 0, 30));

	heliceNodes.push_back(a1);

	AspasMolino* a2 = new AspasMolino(mSM, false, 6, mNode);
	a2->getMainNode()->scale(0.15, 0.15, 0.15);
	a2->getMainNode()->translate(Ogre::Vector3(-300, 0, 30));

	heliceNodes.push_back(a2);
}


void Avion::pilotoNinja()
{
	pilotoNode = mNode->createChildSceneNode();
	Ogre::Entity* ninja = mSM->createEntity("ninja.mesh");
	pilotoNode->attachObject(ninja);

	pilotoNode->yaw(Ogre::Degree(180.0));
}

void Avion::frente()
{
	fernteNode = mNode->createChildSceneNode();
	Ogre::Entity* frente = mSM->createEntity("Barrel.mesh");
	fernteNode->attachObject(frente);

	fernteNode->translate(0, 0, 100);
	fernteNode->pitch(Ogre::Degree(90.0));
	fernteNode->scale(10, 1, 10);
}

void Avion::alaDerecha()
{
	alaDNode = mNode->createChildSceneNode();
	Ogre::Entity* alaDzquierda = mSM->createEntity("Barrel.mesh");
	alaDNode->attachObject(alaDzquierda);

	alaDNode->translate(Ogre::Vector3(160, 0., 0));
	alaDNode->scale(90, 10, 5);
}

void Avion::alaIzquierda()
{
	alaINode = mNode->createChildSceneNode();
	Ogre::Entity* alaIzquierda = mSM->createEntity("Barrel.mesh");
	alaINode->attachObject(alaIzquierda);

	alaINode->translate(Ogre::Vector3(-160, 0., 0));
	alaINode->scale(90, 10, 5);
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) {
		for (auto h : heliceNodes) {
			h->keyPressed(evt);
		}
	}

	return true;
}
