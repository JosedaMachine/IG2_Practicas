#include "AspasMolino.h"
#include <OgreEntity.h>


AspasMolino::AspasMolino(Ogre::SceneManager* mSM, const int& numAspas_)
: mSM(mSM), numAspas(numAspas_){
	arrayAspas.reserve(numAspas);

	mNode = new Ogre::SceneNode(mSM);

	aspasNode = mNode->createChildSceneNode();

	cilindroCentralNode = mNode->createChildSceneNode();

	Ogre::Entity* cilindo = mSM->createEntity("Barrel.mesh");
	cilindroCentralNode->attachObject(cilindo);

	cilindroCentralNode->pitch(Ogre::Degree(90));
	int rad = 1200;
	float ang = 0;
	float pro = 360.0 / numAspas;

	cilindroCentralNode->setScale(rad / 20, 20, rad / 20);

	//las esferas del dragón
	for (int i = 0; i < numAspas; i++) {

		arrayAspas[i] = new Aspa(mSM, "Aspa" + std::to_string(i) );

		arrayAspas[i]->setFather(mNode);
		//Pos original en la x + seno del angulo por el radio
		arrayAspas[i]->getNode()->roll(Ogre::Degree(pro * i));

		arrayAspas[i]->getNode()->translate(rad/2,0,0, Ogre::Node::TS_LOCAL);

	}
}

AspasMolino::~AspasMolino()
{

}

Ogre::SceneNode* AspasMolino::getMain()
{
	return mNode;
}

bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) mNode->roll(Ogre::Degree(2));
	else if (evt.keysym.sym == SDLK_c)cilindroCentralNode->translate(0, -2, 0, Ogre::Node::TS_LOCAL);

	return true;
}

void AspasMolino::setFather(Ogre::SceneNode* f)
{
	f->addChild(mNode);
}

