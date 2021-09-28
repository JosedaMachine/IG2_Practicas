#include "RotorDron.h"
#include <OgreEntity.h>

RotorDron::RotorDron(Ogre::SceneManager* man) {
	mSM = man;
	mNode = mSM->getRootSceneNode()->createChildSceneNode();

	aspasMol = new AspasMolino(mSM, 6, false);
	aspasMol->setFather(mNode);
	aspasMol->getMain()->pitch(Ogre::Degree(90));

	esf = mNode->createChildSceneNode();

	Ogre::Entity* esfera = mSM->createEntity("sphere.mesh");
	esf->attachObject(esfera);

	esf->scale(5, 5, 5);
	esf->translate(0, -500, 0);
}

RotorDron::~RotorDron()
{

}

bool RotorDron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g || evt.keysym.sym == SDLK_c) {
		aspasMol->keyPressed(evt);
	}
	else if (evt.keysym.sym == SDLK_h) {

	}

	return true;
}
