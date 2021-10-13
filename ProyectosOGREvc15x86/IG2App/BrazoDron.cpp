#include "BrazoDron.h"


BrazoDron::BrazoDron(Ogre::SceneNode* mNode_ ,  const bool& clockWise, const int& numAspas/*, Ogre::SceneNode* parent*/): EntityIG(mNode_), numAspas_(numAspas){
    //! if (!parent)
    //!     mNode = mSM->getRootSceneNode()->createChildSceneNode();
    //! else mNode = parent->createChildSceneNode();

    float radio = 50;
    cilindro = mNode->createChildSceneNode();
    Ogre::Entity* cilindro_ = mSM->createEntity("Barrel.mesh");
    cilindro->attachObject(cilindro_);
    cilindro->roll(Ogre::Degree(90.));
    float factor = 0.55;
    cilindro->setScale(radio * 0.55, radio * 3, radio * 0.55);

    rotorNode = mNode->createChildSceneNode();
    rotor = new RotorDron(rotorNode, clockWise, numAspas_);

    float scale = 0.4;
    rotorNode->setScale(scale, scale, scale);
    rotorNode->translate(400, 0, 0);
}

BrazoDron::~BrazoDron()  {
    if (rotor) delete rotor;
}

bool BrazoDron::keyPressed(const OgreBites::KeyboardEvent& evt){
    if (rotor) rotor->keyPressed(evt);

    return true;
}
