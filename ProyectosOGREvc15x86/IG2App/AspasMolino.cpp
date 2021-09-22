#include "AspasMolino.h"
#include <OgreEntity.h>


AspasMolino::AspasMolino(Ogre::SceneManager* mSM, const int& numAspas_)
: mSM(mSM), numAspas(numAspas_){
	arrayAspas.reserve(numAspas);

	mNode = mSM->getRootSceneNode()->createChildSceneNode();

	aspasNode = mNode->createChildSceneNode();

	int rad = 1500;
	float ang = 0;
	float pro = 360.0 / 12;

	//las esferas del dragón
	for (int i = 0; i < 12; i++) {

		arrayAspas[i] = new Aspa(mSM, "Aspa" + std::to_string(i) );

		Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");

		float angle = Ogre::Math::DegreesToRadians(ang);
		//Pos original en la x + seno del angulo por el radio
		arrayAspas[i]->getNode()->setPosition(Ogre::Math::Sin(angle) * rad, Ogre::Math::Cos(angle) * rad, 0);
		ang += pro;

	}
}

AspasMolino::~AspasMolino()
{
}
