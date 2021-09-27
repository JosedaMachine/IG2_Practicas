#include "Molino.h"

Molino::Molino(Ogre::SceneManager* mSM): mSM(mSM){
	mNode = mSM->getRootSceneNode()->createChildSceneNode();

	//Aspas
	blades = new AspasMolino(mSM, 12, mNode);
	blades->getMainNode()->setScale(0.3, 0.3, 0.3);
	blades->getMainNode()->translate(0, 150, 220);

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

void Molino::rotateBlades(const float& degrees) {
	if (blades) {
		blades->getMainNode()->roll(Ogre::Degree(degrees));
		blades->FixOrnamentRot(degrees);
	}
}
