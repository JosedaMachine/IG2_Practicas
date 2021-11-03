#include "Sinbad.h"
#include <OgreEntity.h>


Sinbad::Sinbad(Ogre::SceneNode* _node) : EntityIG(_node){
	Ogre::Entity* cuerpo = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(cuerpo);

	/*runBase = cuerpo->getAnimationState("RunBase");
	runBase->setEnabled(true);
	runBase->setLoop(true);*/

	dance = cuerpo->getAnimationState("Dance");
	dance->setEnabled(true);
	dance->setLoop(true);

	/*runTop = cuerpo->getAnimationState("RunTop");
	runTop->setEnabled(true);
	runTop->setLoop(true);*/

	getAnimationNames(cuerpo);

	//Timer
	myTimer = Ogre::Timer();
	myTimer.reset();
	isStopped = false;

	//mNode->yaw(Ogre::Degree(90.f));
}

Sinbad::~Sinbad() {
}

void Sinbad::getAnimationNames(Ogre::Entity* ent){
	std::cout << "\n";
	Ogre::AnimationStateSet* aux = ent->getAllAnimationStates();
	auto it = aux->getAnimationStateIterator().begin();
	while (it != aux->getAnimationStateIterator().end()){
		auto s = it->first; 
		std::cout << s << "\n";
		++it;
	}
	std::cout << "\n";
}

void Sinbad::frameRendered(Ogre::FrameEvent const& evt) {
	//runBase->addTime(evt.timeSinceLastFrame);
	//runTop->addTime(evt.timeSinceLastFrame);
	dance->addTime(evt.timeSinceLastFrame);

	gira();
}

void Sinbad::gira(){
	if (myTimer.getMilliseconds() > maxTime && !isStopped) {
		isStopped = true;
		myTimerStopped.reset();
		clockWise = Ogre::Math::RangeRandom(-1, 1) < 0 ? 1 : -1;

		timeLimit = Ogre::Math::RangeRandom(1000, maxTime);
		gradesToAdd = 180.0 / ((float)timeLimit * 0.6);

	}
	else if (!isStopped) {
		EL_TRUCO(0.5f);
	}

	if (isStopped) {
		std::cout << gradesToAdd << "\n";
		std::cout << clockWise << "\n";
		//? No gira del todo bien a saber por que
		mNode->yaw(Ogre::Degree(gradesToAdd * clockWise));
		if (myTimerStopped.getMilliseconds() > timeLimit) {
			isStopped = false;
			myTimerStopped.reset();
			myTimer.reset();
		}
	}
}

void Sinbad::EL_TRUCO(float const& degrees) {
	mNode->translate(0.0, -3490, 0.0, Ogre::Node::TS_LOCAL);
	mNode->roll(Ogre::Degree(degrees));
	mNode->translate(0.0, 3490, 0.0, Ogre::Node::TS_LOCAL);
}
