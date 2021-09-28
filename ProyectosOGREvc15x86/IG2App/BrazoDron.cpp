#include "BrazoDron.h"


BrazoDron::BrazoDron(Ogre::SceneManager* mSM_, const int& numAspas): mSM(mSM_), numAspas_(numAspas) {
    mNode = mSM->getRootSceneNode()->createChildSceneNode();

    float radio = 50;
    cilindro = mNode->createChildSceneNode();
    Ogre::Entity* cilindro_ = mSM->createEntity("Barrel.mesh");
    cilindro->attachObject(cilindro_);
    cilindro->roll(Ogre::Degree(90.));
    cilindro->setScale(radio, radio * 3, radio);

    rotorNode = mNode->createChildSceneNode();
    rotor = new RotorDron(mSM, numAspas_, rotorNode);

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
