#include "Avion.h"

#include <iostream>
#include <OgreEntity.h>
Avion::Avion(Ogre::SceneNode * mNode_): EntityIG(mNode_) {
	cuerpoNode = mNode->createChildSceneNode();
	manuallyStopped = false;
	myTimer = Ogre::Timer();
	myTimer.reset();

	Ogre::Entity* cuerpo = mSM->createEntity("sphere.mesh");
	cuerpoAux = cuerpo;
	cuerpo->setMaterialName("Practica1/Red");
	cuerpoNode->attachObject(cuerpo);

	planeAction = ORBITATE;

	helices();

	ToLeft();

	ToRight();
	
	Front();

	NinjaPilot();

	createLight(); 

	createBillBoard();

	setParticleSys();
}

void Avion::createLight(){
	light = mNode->createChildSceneNode();

	Ogre::Light* luz = mSM->createLight();

	luz->setType(Ogre::Light::LT_SPOTLIGHT);
	luz->setDirection(0, -1, 0);
	luz->setSpotlightInnerAngle(Ogre::Degree(16.0f));
	luz->setSpotlightOuterAngle(Ogre::Degree(15.0f));
	luz->setSpotlightFalloff(0.1f);

	light->attachObject(luz);
}

void Avion::createBillBoard(){
	points = mSM->createBillboardSet("Se como Jose", 1);
	float size = 150;
	points->setDefaultDimensions(size, size);
	points->setMaterialName("Practica1/Points");

	cuerpoNode->attachObject(points);
	Ogre::Billboard* bb = points->createBillboard(Ogre::Vector3(10 + size, 0, 0));
}

void Avion::restablishTextures() {
	//material por defecto
	cuerpoAux->setMaterialName("BaseWhite");
	alaIAux->setMaterialName("Practica1/Wings");
	alaDAux->setMaterialName("Practica1/Wings");
}

void Avion::orbitate(){
	if (!manuallyStopped) {
		if (myTimer.getMilliseconds() > maxTime && !isStopped) {
			isStopped = true;
			myTimerStopped.reset();
			clockWise = Ogre::Math::RangeRandom(-1, 1) < 0 ? 1 : -1;

			timeLimit = Ogre::Math::RangeRandom(1000, maxTime);
			gradesToAdd = 180.0 / ((float)timeLimit * 0.6);

		}
		else if (!isStopped) {
			EL_TRUCO_Vertical(0.5f);
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
	else {
		for (auto h : heliceNodes) {
			h->rotate();
		}
	}
}

void Avion::overflyOgre(){
	EL_TRUCO_Horizontal(0.2f);

	for (auto h : heliceNodes) {
		h->rotate();
	}
}

void Avion::receiveEvent(Message mes,EntityIG* entidad)
{
	switch (mes.m)
	{
	case R:
		manuallyStopped = !manuallyStopped;

		if (manuallyStopped) {
			cuerpoAux->setMaterialName("Practica1/Red");
			alaDAux->setMaterialName("Practica1/Red");
			alaIAux->setMaterialName("Practica1/Red");
		}
		else restablishTextures();

		break;
	default:
		break;
	}
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
	ninja->setMaterialName("Practica1/Yellow");
	pilotoNode->attachObject(ninja);

	pilotoNode->yaw(Ogre::Degree(90.0));
}

void Avion::Front()
{
	fernteNode = mNode->createChildSceneNode();
	Ogre::Entity* frente = mSM->createEntity("Barrel.mesh");
	frente->setMaterialName("Practica1/Brown");
	fernteNode->attachObject(frente);

	fernteNode->translate(-100, 0, 0);
	fernteNode->roll(Ogre::Degree(90.0));
	fernteNode->scale(10, 1, 10);
}

void Avion::ToRight() {
	alaDNode = mNode->createChildSceneNode();
	Ogre::Entity* alaDerecha = mSM->createEntity("cube.mesh");
	alaDAux = alaDerecha;
	alaDerecha->setMaterialName("Practica1/Wings");
	alaDNode->attachObject(alaDerecha);

	alaDNode->translate(Ogre::Vector3(30, 0., 200));
	alaDNode->scale(1.2, 0.2, 4);
}

void Avion::ToLeft() {
	alaINode = mNode->createChildSceneNode();
	Ogre::Entity* alaIzquierda = mSM->createEntity("cube.mesh");
	alaIAux = alaIzquierda;
	alaIzquierda->setMaterialName("Practica1/Wings");
	alaINode->attachObject(alaIzquierda);
	
	alaINode->translate(Ogre::Vector3(30, 0., -200));
	alaINode->scale(1.2, 0.2, 4);
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_g) {
		for (auto h : heliceNodes) {
			h->keyPressed(evt);
		}
	}

	if (evt.keysym.sym == SDLK_r && ex == nullptr) {
		mNode->setVisible(false);

		ex = mSM->createParticleSystem("PedroPicaPiedra","IG2App/ExplosionSmoke");
		ex->setEmitting(true);
		cuerpoNode->attachObject(ex);
		ex->setVisible(true);
		setPlaneAction(NOTHING);

		sendEvent(Message(Messages::Samir));
	}
	return true;
}

void Avion::frameRendered(Ogre::FrameEvent const& evt) {
	if (planeAction == OVERFLY) {
		overflyOgre();
	}
	else if(planeAction == ORBITATE){
		orbitate();
	}
}

void Avion::EL_TRUCO_Vertical(float const& degrees){
	mNode->translate(0.0, -3600, 0.0, Ogre::Node::TS_LOCAL);
	mNode->roll(Ogre::Degree(degrees));
	mNode->translate(0.0, 3600, 0.0, Ogre::Node::TS_LOCAL);
}

void Avion::EL_TRUCO_Horizontal(float const& degrees){
	mNode->translate(0.0, -500, 500, Ogre::Node::TS_LOCAL);
	mNode->yaw(Ogre::Degree(degrees));
	mNode->translate(0.0, 500, -500, Ogre::Node::TS_LOCAL);
}

void Avion::setPlaneAction(ACTION act){
	planeAction = act;
}

void Avion::setParticleSys(){
	pSys = mSM->createParticleSystem("psSmoke", "IG2App/Smoke");
	pSys->setEmitting(true);
	cuerpoNode->attachObject(pSys);
}
