#include "AspasMolino.h"


AspasMolino::AspasMolino(Ogre::SceneManager* mSM, const int& numAspas_, Ogre::SceneNode* parentNode)
: mSM(mSM), numAspas(numAspas_){
	arrayAspas.reserve(numAspas);

	if(!parentNode)
		mNode = mSM->getRootSceneNode()->createChildSceneNode();
	else mNode = parentNode->createChildSceneNode();
	//aspasNode = mNode->createChildSceneNode();

	int radi = 50;
	cilindroCentralNode = mNode->createChildSceneNode();
	Ogre::Entity* tablero = mSM->createEntity("Barrel.mesh");
	cilindroCentralNode->attachObject(tablero);
	cilindroCentralNode->pitch(Ogre::Degree(90.));
	cilindroCentralNode->setScale(radi, 20, radi);

	int radio = 500;
	float ang = 90;
	float proportion = 360.0 / numAspas;

	////las esferas del dragón
	for (int i = 0; i < numAspas; i++) {
		arrayAspas[i] = new Aspa(mSM, "Aspa" + std::to_string(i), mNode);
		float angle = Ogre::Math::DegreesToRadians(ang);
		arrayAspas[i]->getMainNode()->roll(Ogre::Degree(ang));
		arrayAspas[i]->getOrnamentNode()->roll(Ogre::Degree(-ang));
		arrayAspas[i]->getMainNode()->setPosition(Ogre::Math::Cos(angle) * radio, Ogre::Math::Sin(angle) * radio, 0);
		ang += proportion;
	}
}

AspasMolino::~AspasMolino() {
	for (Aspa* asp : arrayAspas){
		delete asp;
	}

	//if(cilindroCentralNode)
	//	delete cilindroCentralNode;
}

void AspasMolino::FixOrnamentRot(const float& rotation) {
	for (int i = 0; i < numAspas; i++) {
		arrayAspas[i]->getOrnamentNode()->roll(Ogre::Degree(-rotation));
	}
}
