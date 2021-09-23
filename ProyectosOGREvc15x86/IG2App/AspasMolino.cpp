#include "AspasMolino.h"
#include <OgreEntity.h>


AspasMolino::AspasMolino(Ogre::SceneManager* mSM, const int& numAspas_)
: mSM(mSM), numAspas(numAspas_){
	arrayAspas.reserve(numAspas);

	mNode = mSM->getRootSceneNode()->createChildSceneNode();

	aspasNode = mNode->createChildSceneNode();

	int rad = 1200;
	float ang = 0;
	float pro = 360.0 / numAspas;

	//las esferas del dragón
	for (int i = 0; i < numAspas; i++) {

		arrayAspas[i] = new Aspa(mSM, "Aspa" + std::to_string(i) );

		Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");

		//float angle = Ogre::Math::DegreesToRadians(ang);
		//Pos original en la x + seno del angulo por el radio
		arrayAspas[i]->getNode()->roll(Ogre::Degree(pro * i));

		arrayAspas[i]->getNode()->translate(rad/2,0,0, Ogre::Node::TS_LOCAL);
		//ang += pro;

	}
}

AspasMolino::~AspasMolino()
{

}
