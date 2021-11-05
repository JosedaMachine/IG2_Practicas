#include "Sinbad.h"
#include <OgreEntity.h>


Sinbad::Sinbad(Ogre::SceneNode* _node) : EntityIG(_node){
	cuerpo = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(cuerpo);
	
	hasSwords = false;
	isDancing = false;

	swordL = mSM->createEntity("Sword.mesh");
	swordR = mSM->createEntity("Sword.mesh");
	swordL->setVisible(false);
	cuerpo->attachObjectToBone("Handle.R", swordL);
	swordR->setVisible(false);
	cuerpo->attachObjectToBone("Handle.L", swordR);

	runBase = cuerpo->getAnimationState("RunBase");
	runBase->setEnabled(true);
	runBase->setLoop(true);

	dance = cuerpo->getAnimationState("Dance");
	dance->setEnabled(true);
	dance->setLoop(true);

	runTop = cuerpo->getAnimationState("RunTop");
	runTop->setEnabled(true);
	runTop->setLoop(true);

	getAnimationNames(cuerpo);

	//Timer
	myTimer = Ogre::Timer();
	myTimer.reset();
	isStopped = false;
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
	if (!isDancing) {
		runBase->addTime(evt.timeSinceLastFrame);
		runTop->addTime(evt.timeSinceLastFrame);
	}
	else {
		dance->addTime(evt.timeSinceLastFrame);
	}

	//gira();
}

void Sinbad::gira(){
	if (myTimer.getMilliseconds() > maxTime && !isStopped) {
		isStopped = true;
		myTimerStopped.reset();
		clockWise = Ogre::Math::RangeRandom(-1, 1) < 0 ? 1 : -1;

		timeLimit = Ogre::Math::RangeRandom(1000, maxTime);
		gradesToAdd = (180.0 / ((float)timeLimit) ) * 20.0f;

	}
	else if (!isStopped) {
		EL_TRUCO(0.7f);
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

void Sinbad::arma(bool left){
	if (!swordL->isVisible() && !swordR->isVisible()) {
		int i = Ogre::Math::RangeRandom(0, 1);
		if (i) swordL->setVisible(false);
		else swordR->setVisible(false);
	}
}

void Sinbad::arma(){
	if (!hasSwords) {
		swordL->setVisible(true);
		swordR->setVisible(true);
	}
	else {
		swordL->setVisible(true);
		swordR->setVisible(true);
	}

	hasSwords = !hasSwords;
}

void Sinbad::cambiaEspada(){
	if (swordL->isVisible()) {
		swordL->setVisible(false);
		swordR->setVisible(true);
	}
	else {
		swordL->setVisible(true);
		swordR->setVisible(false);
	}
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt){
	if (evt.keysym.sym == SDLK_j) {
		isDancing = !isDancing;
		std::cout << "Cambia de anim\n";
	}
	return false;
}

void Sinbad::EL_TRUCO(float const& degrees) {
	mNode->translate(0.0, -3490, 0.0, Ogre::Node::TS_LOCAL);
	mNode->pitch(Ogre::Degree(degrees));
	mNode->translate(0.0, 3490, 0.0, Ogre::Node::TS_LOCAL);
}
