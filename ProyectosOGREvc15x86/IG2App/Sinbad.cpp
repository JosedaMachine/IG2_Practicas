#include "Sinbad.h"
#include <OgreEntity.h>


Sinbad::Sinbad(Ogre::SceneNode* _node) : EntityIG(_node){
	Ogre::Entity* cuerpo = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(cuerpo);

}

Sinbad::~Sinbad() {
}
