#include "Avion.h"

#include <iostream>
Avion::Avion(Ogre::SceneNode * mNode_): EntityIG(mNode_) {
	cuerpoNode = mNode->createChildSceneNode();
	

	myTimer = Ogre::Timer();
	myTimer.reset();

	Ogre::Entity* cuerpo = mSM->createEntity("sphere.mesh");
	cuerpoNode->attachObject(cuerpo);
	helices();

	ToLeft();

	ToRight();
	
	Front();

	NinjaPilot();

	createLight(); 
}

void Avion::createLight()
{
	std::cout << "\n\nME CAGO EN MI PUTA MADRE 100 PUTAS VECES ODIO IG\n\n";
	light = mNode->createChildSceneNode();

	Ogre::Light* luz = mSM->createLight();

	luz->setType(Ogre::Light::LT_SPOTLIGHT);
	luz->setDirection(0, -1, 0);
	luz->setSpotlightInnerAngle(Ogre::Degree(16.0f));
	luz->setSpotlightOuterAngle(Ogre::Degree(15.0f));
	luz->setSpotlightFalloff(0.1f);

	light->attachObject(luz);
}

void Avion::helices() {

	Ogre::SceneNode* aspa1 = mNode->createChildSceneNode();
	AspasMolino* a1 = new AspasMolino(aspa1, false, 6);
	a1->getMainNode()->scale(0.15, 0.15, 0.15);
	a1->getMainNode()->translate(Ogre::Vector3(-30, 0, 300));
	a1->getMainNode()->yaw(Ogre::Degree(90.0));

	heliceNodes.push_back(a1);

	Ogre::SceneNode* aspa2 = mNode->createChildSceneNode();
	AspasMolino* a2 = new AspasMolino(aspa2, false, 6);

	
	a2->getMainNode()->scale(0.15, 0.15, 0.15);
	a2->getMainNode()->translate(Ogre::Vector3(-30, 0, -300));
	a2->getMainNode()->yaw(Ogre::Degree(90.0));

	heliceNodes.push_back(a2);
}


void Avion::NinjaPilot() {
	pilotoNode = mNode->createChildSceneNode();
	Ogre::Entity* ninja = mSM->createEntity("ninja.mesh");
	pilotoNode->attachObject(ninja);

	pilotoNode->yaw(Ogre::Degree(90.0));
}

void Avion::Front()
{
	fernteNode = mNode->createChildSceneNode();
	Ogre::Entity* frente = mSM->createEntity("Barrel.mesh");
	fernteNode->attachObject(frente);

	fernteNode->translate(-100, 0, 0);
	fernteNode->roll(Ogre::Degree(90.0));
	fernteNode->scale(10, 1, 10);
}

void Avion::ToRight()
{
	alaDNode = mNode->createChildSceneNode();
	Ogre::Entity* alaDzquierda = mSM->createEntity("Barrel.mesh");
	alaDNode->attachObject(alaDzquierda);

	alaDNode->translate(Ogre::Vector3(0, 0., 160));
	alaDNode->scale(5, 10, 90);
}

void Avion::ToLeft()
{
	alaINode = mNode->createChildSceneNode();
	Ogre::Entity* alaIzquierda = mSM->createEntity("Barrel.mesh");
	alaINode->attachObject(alaIzquierda);

	alaINode->translate(Ogre::Vector3(0, 0., - 160));
	alaINode->scale(5, 10, 90);
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_g) {
		for (auto h : heliceNodes) {
			h->keyPressed(evt);
		}
	}

	return true;
}

void Avion::frameRendered(Ogre::FrameEvent const& evt) {
	if (myTimer.getMilliseconds() > maxTime && !isStopped) {
		isStopped = true;
		myTimerStopped.reset();
		clockWise = Ogre::Math::RangeRandom(-1, 1) < 0 ? 1 : -1;

		timeLimit = Ogre::Math::RangeRandom(1000, maxTime);
		gradesToAdd = 180.0 / ((float)timeLimit * 0.6);

	}
	else if (!isStopped) {
		EL_TRUCO(0.5f);
		for (auto h : heliceNodes) {
			h->rotate();
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

void Avion::EL_TRUCO(float const& degrees){
	mNode->translate(0.0, -3600, 0.0, Ogre::Node::TS_LOCAL);
	mNode->roll(Ogre::Degree(degrees));
	mNode->translate(0.0, 3600, 0.0, Ogre::Node::TS_LOCAL);
}
