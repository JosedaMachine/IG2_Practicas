#include "Dron.h"

Dron::Dron(Ogre::SceneManager* mSM_, const int& numArms, const int& numAspas, Ogre::SceneNode* father): mSM(mSM_), numArms_(numArms), numAspas_(numAspas) {
	if (!father)mNode = mSM->getRootSceneNode()->createChildSceneNode();
	else mNode = father->createChildSceneNode();

    sphere = mNode->createChildSceneNode();
    Ogre::Entity* cuerpo = mSM->createEntity("sphere.mesh");
    sphere->attachObject(cuerpo);

    float scale = 3;
    sphere->setScale(scale, scale, scale);

    float proportion = 360. / numArms;
    float iniAngel = 0;
    float radio = 400;

    for (size_t i = 0; i < numArms_ ; i++) {

        Ogre::SceneNode* node = mNode->createChildSceneNode();
        
        bool clockWise = true;
        if (i % 2) clockWise = false;
        
        BrazoDron* brazo = new BrazoDron(mSM,clockWise, numAspas, node);
        armNodes.push_back({ node, brazo });

        float angle = Ogre::Math::DegreesToRadians(iniAngel);
        armNodes[i].first->yaw(Ogre::Degree(-iniAngel));
        

        //? Aqui saco el brazo en el eje X, para que no te deo algo feo
        armNodes[i].first->setPosition(Ogre::Math::Cos(angle) * radio * ( i == numArms/2 ? 1.5 : 1), 0, Ogre::Math::Sin(angle) * radio);
        iniAngel += proportion;
    }

    mNode->yaw(Ogre::Degree(90.));
}


Dron::~Dron() {
    for (ArmNodes arm : armNodes)
        delete arm.second;

    armNodes.clear();
}

bool Dron::keyPressed(const OgreBites::KeyboardEvent& evt){
    for (ArmNodes arm : armNodes)
        arm.second->keyPressed(evt);
    
    return true;
}
