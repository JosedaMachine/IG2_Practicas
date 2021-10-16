#include "Dron.h"
#include <iostream>

Dron::Dron(Ogre::SceneNode * mNode_, const int& numArms, const int& numAspas): numArms_(numArms), numAspas_(numAspas), EntityIG(mNode_) {
    sphere = mNode->createChildSceneNode();
    Ogre::Entity* cuerpo = mSM->createEntity("sphere.mesh");
    sphere->attachObject(cuerpo);

    myTimer = Ogre::Timer();
    myTimer.reset();

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

	light = mNode->createChildSceneNode();

	//? Preguntar por que las luces nos van al reves(a ser posible
	//? a guacamole)

	Ogre::Light* luz = mSM->createLight();
	luz->setType(Ogre::Light::LT_SPOTLIGHT);
	luz->setDirection(0, -1, 0);
	luz->setSpotlightInnerAngle(Ogre::Degree(16.0f));
	luz->setSpotlightOuterAngle(Ogre::Degree(15.0f));

	//! La forma que se expande hacia los lados(Dice oscar)
	//! Que le ha preguntado al tip
	luz->setSpotlightFalloff(0.1f);

	light->attachObject(luz);

    isStopped = false;
    manualyStopped = false;
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
        EL_TRUCO(2.);

        //Ficticio
        
    }
    
    return true;
}

void Dron::frameRendered(Ogre::FrameEvent const& evt){
	if (!manualyStopped) {

		if (myTimer.getMilliseconds() > maxTime && !isStopped) {
			isStopped = true;
			myTimerStopped.reset();
			clockWise = Ogre::Math::RangeRandom(-1, 1) < 0 ? 1 : -1;

			timeLimit = Ogre::Math::RangeRandom(1000, maxTime);
			gradesToAdd = 180.0 / ((float)timeLimit * 0.6);

		}
		else if (!isStopped) {
			EL_TRUCO(0.5f);
			
			for (auto a : armNodes) {
				a.second->rotateAspas();
			}
		}

		if (isStopped) {
			mNode->yaw(Ogre::Degree(gradesToAdd * clockWise));
			if (myTimerStopped.getMilliseconds() > timeLimit) {
				isStopped = false;
				myTimerStopped.reset();
				myTimer.reset();
			}
		}
	}
	else {
		for (auto a : armNodes) {
			a.second->rotateAspas();
		}
	}
}

void Dron::EL_TRUCO(float const & degrees) {
    mNode->translate(0.0, -3600, 0.0, Ogre::Node::TS_LOCAL);
    mNode->roll(Ogre::Degree(degrees));
    mNode->translate(0.0, 3600, 0.0, Ogre::Node::TS_LOCAL);
}

void Dron::FICTICIO() {
    //if (ficticioDroneNode) ficticioDroneNode->pitch(Ogre::Degree(2));
}

void Dron::receiveEvent(Message mes, EntityIG* entidad)
{
	switch (mes.m)
	{
	case R:
		manualyStopped = true;
		break;
	default:
		break;
	}
}
