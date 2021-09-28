#include "Molino.h"

Molino::Molino(Ogre::SceneManager* mSM): mSM(mSM){
	mNode = mSM->getRootSceneNode()->createChildSceneNode();

	//Aspas
	radioAspasMolino = 220;
	aspas = mNode->createChildSceneNode();
	blades = new AspasMolino(mSM, true, 12, aspas);
	blades->getMainNode()->setScale(0.3, 0.3, 0.3);
	blades->getMainNode()->translate(0, 150, radioAspasMolino);

	////CuerpoMolino
	float radio = 80;
	float altura = 80;
	body = mNode->createChildSceneNode();
	Ogre::Entity* cuerpo = mSM->createEntity("Barrel.mesh");
	body->attachObject(cuerpo);
	body->setScale(radio, altura, radio);

	//Tapa Molino
	float radioSphere = 2.1;
	tap = mNode->createChildSceneNode();
	Ogre::Entity* tapa = mSM->createEntity("sphere.mesh");
	tap->attachObject(tapa);
	tap->translate(0, altura*2.5, 0);
	tap->setScale(radioSphere, radioSphere, radioSphere);
}

Molino::~Molino() {
	if(blades) delete blades;
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt){
	blades->keyPressed(evt);

	if (evt.keysym.sym == SDLK_h) {
		//rotar1(1.);
		rotar2(1.);
	}
	return true;
}

void Molino::rotar1(const float& angle) {
	aspas->yaw(Ogre::Degree(angle));
}

void Molino::rotar2(const float& angle) {
	blades->getMainNode()->translate(0, 0, -radioAspasMolino, Ogre::Node::TS_LOCAL);
	blades->getMainNode()->yaw(Ogre::Degree(angle));
	blades->getMainNode()->translate(0, 0, radioAspasMolino, Ogre::Node::TS_LOCAL);
}