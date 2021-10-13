#include "Dron.h"

Dron::Dron(Ogre::SceneNode * mNode_, const int& numArms, const int& numAspas): numArms_(numArms), numAspas_(numAspas), EntityIG(mNode_) {
    sphere = mNode->createChildSceneNode();
    Ogre::Entity* cuerpo = mSM->createEntity("sphere.mesh");
    sphere->attachObject(cuerpo);

    float scale = 3;
    sphere->setScale(scale, scale, scale);

    float proportion = 360. / numArms;
    float iniAngle = 0;
    float radio = 400;

    for (size_t i = 0; i < numArms_ ; i++) {

        Ogre::SceneNode* node = mNode->createChildSceneNode();
        
        bool clockWise = true;
        if (i % 2) clockWise = false;


        //BrazoDron* brazo = new BrazoDron(mSM,clockWise, numAspas, node); //Lo de antes
        BrazoDron* brazo = new BrazoDron(node,clockWise, numAspas);
        armNodes.push_back({ node, brazo });

        float angle = Ogre::Math::DegreesToRadians(iniAngle);
        armNodes[i].first->yaw(Ogre::Degree(-iniAngle));
        

        //? Aqui saco el brazo en el eje X, para que no te deo algo feo
        armNodes[i].first->setPosition(Ogre::Math::Cos(angle) * radio * ( i == numArms/2 ? 1.5 : 1), 0, Ogre::Math::Sin(angle) * radio);
        iniAngle += proportion;
    }

    mNode->yaw(Ogre::Degree(90.));
}


Dron::~Dron() {
    for (ArmNodes arm : armNodes)
        delete arm.second;

    armNodes.clear();
}

bool Dron::keyPressed(const OgreBites::KeyboardEvent& evt){

    if (evt.keysym.sym == SDLK_j) mNode->yaw(Ogre::Degree(2));
    else if (evt.keysym.sym == SDLK_g)
        for (ArmNodes arm : armNodes)
            arm.second->keyPressed(evt);
    else if (evt.keysym.sym == SDLK_h) {

        //El truco
        mNode->translate(0.0, -3600, 0.0, Ogre::Node::TS_LOCAL);
        mNode->roll(Ogre::Degree(2.));
        mNode->translate(0.0, 3600, 0.0, Ogre::Node::TS_LOCAL);

        //Ficticio
        //if (ficticioDroneNode) ficticioDroneNode->pitch(Ogre::Degree(2));
    }
    
    return true;
}
