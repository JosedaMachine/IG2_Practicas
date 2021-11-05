#include "Bomba.h"
#include <OgreEntity.h>

Bomba::Bomba(Ogre::SceneNode* _node) : EntityIG(_node) {
    Ogre::Entity* bomba = mSM->createEntity("Barrel.mesh");
    bomba->setMaterialName("Practica1/Wings");
    mNode->attachObject(bomba);
}

Bomba::~Bomba(){
}

void Bomba::frameRendered(Ogre::FrameEvent const& evt)
{
}

bool Bomba::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    return false;
}
