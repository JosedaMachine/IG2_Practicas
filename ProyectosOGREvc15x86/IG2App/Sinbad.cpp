#include "Sinbad.h"
#include <OgreEntity.h>


Sinbad::Sinbad(Ogre::SceneNode* _node) : EntityIG(_node){
	cuerpo = mSM->createEntity("Sinbad.mesh");

	animationNode = mNode->createChildSceneNode();
	animationNode->attachObject(cuerpo);

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

	if(route) route->addTime(evt.timeSinceLastFrame);
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

void Sinbad::routeAnim(){
	float duracion = 17.f;
	Vector3 scale = mNode->getScale();
	//TODO Animation
	Ogre::Animation* animation = mSM->createAnimation("Ruta", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(animationNode);
	//TODO Pos Inicial , Orientacion y duraciones
	Ogre::Vector3 keyframePosAux(0.0);
	Ogre::Vector3 src(0, 0, 1); // posición y orientación iniciales
	Ogre::Real durPaso = duracion / 6.0;  // uniformes
	//TODO KEYFRAMES -> Usaremos un solo keyframe para settear la pos y rot en cada momento
	Ogre::TransformKeyFrame* kfAux;  // 4 keyFrames: origen(0), abajo, arriba, origen(3)
	//! Keyframe 1: origen
	kfAux = track->createNodeKeyFrame(durPaso * 0);
	kfAux->setTranslate(keyframePosAux);
	kfAux->setRotation(src.getRotationTo(Ogre::Vector3(0, 0, 1)));
	//! Keyframe 2
	kfAux = track->createNodeKeyFrame(durPaso * 0.5);
	kfAux->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, -1)));
	//! Keyframe 2
	kfAux = track->createNodeKeyFrame(durPaso * 1);
	kfAux->setRotation(src.getRotationTo(Ogre::Vector3(1, 0, -1)));
	Vector3 posX = Ogre::Vector3::NEGATIVE_UNIT_X * initalPoint.x + Ogre::Vector3::UNIT_X * finalPoint.x;
	Vector3 posZ = Ogre::Vector3::NEGATIVE_UNIT_Z * initalPoint.z + Ogre::Vector3::UNIT_Z * finalPoint.z;
	keyframePosAux += posX * (scale.x / 50.f) + posZ * (scale.z / 50.f);
	kfAux->setTranslate(keyframePosAux);
	//! Keyframe 3 
	kfAux = track->createNodeKeyFrame(durPaso * 4);
	kfAux->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 1)));
	kfAux->setTranslate(keyframePosAux);
	//! Keyframe 4
	kfAux = track->createNodeKeyFrame(durPaso * 4.5);
	kfAux->setRotation(src.getRotationTo(Ogre::Vector3(-1, 0, 1)));
	posX = Ogre::Vector3::UNIT_X * initalPoint.x  + Ogre::Vector3::NEGATIVE_UNIT_X * finalPoint.x;
	posZ = Ogre::Vector3::UNIT_Z * initalPoint.z  + Ogre::Vector3::NEGATIVE_UNIT_Z * finalPoint.z;
	keyframePosAux += posX * (scale.x / 50.f)  + posZ * (scale.z / 50.f);
	kfAux->setTranslate(keyframePosAux);
	//! Keyframe 5
	kfAux = track->createNodeKeyFrame(durPaso * 6);
	kfAux->setRotation(src.getRotationTo(Ogre::Vector3(0, 0, 1)));
	kfAux->setTranslate(keyframePosAux);
	//TODO Relacionar la animación con un Estado 
	route = mSM->createAnimationState("Ruta");
	route->setLoop(true);
	route->setEnabled(true);
}

void Sinbad::setRoute(Vector3 const& intial, Vector3 const& final){
	initalPoint = intial;
	finalPoint = finalPoint;

	routeAnim();
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
