#include "AspasMolino.h"

#include <iostream>
AspasMolino::AspasMolino(Ogre::SceneNode * mNode_, bool hasOrnament, const int& numAspas_)
: numAspas(numAspas_), EntityIG(mNode_) {
	arrayAspas.reserve(numAspas);

	int radi = 50;
	cilindroCentralNode = mNode->createChildSceneNode();
	Ogre::Entity* tablero = mSM->createEntity("Barrel.mesh");
	cilindroCentralNode->attachObject(tablero);
	cilindroCentralNode->pitch(Ogre::Degree(90.));
	cilindroCentralNode->setScale(radi, 20, radi);

	int radio = 500;
	float ang = 90;
	float proportion = 360.0 / numAspas;

	aspasNode = mNode->createChildSceneNode();

	for (int i = 0; i < numAspas; i++) {
		arrayAspas[i] = new Aspa(mSM, aspasNode, hasOrnament);
		float angle = Ogre::Math::DegreesToRadians(ang);
		arrayAspas[i]->getMainNode()->roll(Ogre::Degree(ang));

		Ogre::SceneNode* adorno = arrayAspas[i]->getOrnamentNode();
		if (adorno)  adorno->roll(Ogre::Degree(-ang));
		arrayAspas[i]->getMainNode()->setPosition(Ogre::Math::Cos(angle) * radio, Ogre::Math::Sin(angle) * radio, 0);
		ang += proportion;
	}
}

AspasMolino::~AspasMolino() {
	for (Aspa* asp : arrayAspas){
		delete asp;
	}
	arrayAspas.clear();
}

bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt){
	std::cout << "funka Andres\n";
	if (evt.keysym.sym == SDLK_g) {
	std::cout << "funka Andres2\n";
		aspasNode->roll(Ogre::Degree(degrees));
		FixOrnamentRot(degrees);
	}
	else if (evt.keysym.sym == SDLK_c) {
	std::cout << "funka Andres5\n";
		cilindroCentralNode->translate(0, 0, -100);
	}

	return true;
}

void AspasMolino::FixOrnamentRot(const float& rotation) {
	for (int i = 0; i < numAspas; i++) {
		if (arrayAspas[i]->hasOrnament()) {
			arrayAspas[i]->getOrnamentNode()->roll(Ogre::Degree(-rotation));
		}
	}
}

void AspasMolino::setClockWise(const bool& state) {
	clockWise = state;
	if (!clockWise) degrees *= -1;
}
