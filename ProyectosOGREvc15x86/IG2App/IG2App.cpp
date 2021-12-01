#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMeshManager.h>

#include "CheckML.h"
#include <iostream>

using namespace Ogre;
//! Ahora a las entidades les pasamos : mSM->getRootSceneNode()->createChildSceneNode()
//! porque heredan de entityIg y este solo recibe un nodo. Si queremos que sea hijo de P, le pasamos el nodo 
//! de P

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_ESCAPE) getRoot()->queueEndRendering();
	else if (evt.keysym.sym == SDLK_g && reloj != nullptr) reloj->roll(Ogre::Degree(2));
	else if (evt.keysym.sym == SDLK_h) {
		if (centroEsferas)centroEsferas->roll(Ogre::Degree(2));
	}
	else if (evt.keysym.sym == SDLK_r) {
		entidades[0]->sendEvent(Message(Messages::R));
	}
	//! ONgo bongo Buga Buga Bo 
	return true;
}

void IG2App::BallClock(float rad) {
	reloj = mSM->getRootSceneNode()->createChildSceneNode("Reloj");

	centroEsferas = reloj->createChildSceneNode("centroEsferas");
	float ang = 0;
	float pro = 360.0 / 12;

	//las esferas del drag�n
	for (int i = 0; i < 12; i++) {
		Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");

		mHourNode[i] = centroEsferas->createChildSceneNode("Hora" + std::to_string(i));
		mHourNode[i]->attachObject(sphere);

		float angle = Ogre::Math::DegreesToRadians(ang);
		//Pos original en la x + seno del angulo por el radio
		mHourNode[i]->setPosition(Ogre::Math::Sin(angle) * rad, Ogre::Math::Cos(angle) * rad, 0);
		ang += pro;

		//Hacer m�s peque�as las pares
		//if(i%2 == 0) mHourNode[i]->setScale(0.5, 0.5, 0.5);
	}

	//Hacerlas m�s peque�as
	for (int i = 0; i < 12; i = i + 2)
		mSM->getSceneNode("Hora" + std::to_string(i))->setScale(0.4, 0.4, 0.4);

	//Como decia Melendi, las manecillas del reloj
	for (int i = 0; i < 3; i++) {
		Ogre::Entity* manecilla = mSM->createEntity("cube.mesh");

		manecillas[i] = reloj->createChildSceneNode("Manecilla" + std::to_string(i));
		manecillas[i]->attachObject(manecilla);
	}

	//Configurar para que de igual el tama�o, se ponga bien
	manecillas[0]->setScale(0.3, 8, 0.3);
	manecillas[0]->setPosition(-350, -200, 0);
	manecillas[0]->roll(Ogre::Degree(-60));

	manecillas[1]->setScale(7, 0.7, 0.6);
	manecillas[1]->setPosition(300, 0, 0);

	manecillas[2]->setScale(0.5, -10, 0.6);
	manecillas[2]->setPosition(0, 400, 0);

}

void IG2App::setCamNLight() {
	// create the camera
	Camera* cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(50000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1660);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	mCamNode->setDirection(Ogre::Vector3(0, 1, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

	//------------------------------------------------------------------------
	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	float color = 1.0f;
	luz->setDiffuseColour(color, color, color);
	luz->setDirection(Ogre::Vector3(0, -1, -1));

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);
}

void IG2App::shutdown() {
	mShaderGenerator->removeSceneManager(mSM);
	mSM->removeRenderQueueListener(mOverlaySystem);

	mRoot->destroySceneManager(mSM);

	delete mTrayMgr;  mTrayMgr = nullptr;
	delete mCamMgr; mCamMgr = nullptr;

	entidades.clear();

	// do not forget to call the base 
	IG2ApplicationContext::shutdown();
}

void IG2App::setup(void) {
	// do not forget to call the base first
	IG2ApplicationContext::setup();

	mSM = mRoot->createSceneManager();

	// register our scene with the RTSS
	mShaderGenerator->addSceneManager(mSM);

	mSM->addRenderQueueListener(mOverlaySystem);

	mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	addInputListener(mTrayMgr);

	addInputListener(this);
	setupScene();
}

void IG2App::setupScene(void) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	setCamNLight();

	scene1_2();

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);
}

#pragma region PRACTICA2
//TODO:Configurar bien las teclas
//TODO:Vaiven de la bomba mucho
//TODO:mezclado movimiento sinbad
//TODO:no para la bomba con la tecla
//TODO:No mezcla textura mostaza
void IG2App::scene1_2(){

	mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -20), "Practica1/space", 1, 1, true, 1.0, 100, 100);

	Vector3 iniPos = { -385, 10, 250 }, finalPos = { 385, 10, -250 };

	//! BOMBA
	Bomba* b = new Bomba(mSM->getRootSceneNode()->createChildSceneNode());
	//a->getMainNode()->setPosition(0, 3700, 0);
	//Hay que hacer otro nodo fuera
	b->getMainNode()->setScale(Vector3(10.0));
	addInputListener(b);
	b->addListener(b);
	entidades.push_back(b);

	//! AVION
	Avion* a = new Avion(mSM->getRootSceneNode()->createChildSceneNode());
	a->getMainNode()->setScale(Vector3(0.3f));
	a->getMainNode()->setPosition(0, 500, -500);
	a->setPlaneAction(Avion::OVERFLY);
	a->setFinalSceneConfig();
	addInputListener(a);
	entidades.push_back(a);


	//! AGUA
	Camera* camRef = mSM->createCamera("RefCam");
	camRef->setNearClipDistance(1);
	camRef->setFarClipDistance(50000);
	mCamNode->attachObject(camRef);

	Plano* p = new Plano(mSM->getRootSceneNode()->createChildSceneNode(),
		"mPlane1080x800_2", { 1080 , 800 }, { 100, 80 });
	p->setMaterial("Practica1/Jaja");
	addInputListener(p);
	p->setReflejo(camRef);
	entidades.push_back(p);

	//! Plano Amarillo
	Plano* pAmarillo = new Plano(mSM->getRootSceneNode()->createChildSceneNode(),
		"mPlane1080x800_3", { 300 , 300 }, { 100, 80 });
	pAmarillo->setMaterial("Practica1/Yellow");
	pAmarillo->getMainNode()->translate(Vector3(iniPos));
	entidades.push_back(pAmarillo);

	//! Sinbad
	Sinbad* sinBad = new Sinbad(mSM->getRootSceneNode()->createChildSceneNode());
	addInputListener(sinBad);
	sinBad->addListener(sinBad);
	entidades.push_back(sinBad);

	sinBad->arma();
	sinBad->getMainNode()->scale(Vector3(10));
	Vector3 posOgreIni = iniPos, posOgreFin = finalPos;
	posOgreIni.y = posOgreFin.y = 62;
	sinBad->getMainNode()->translate(posOgreIni);
	sinBad->setRoute(posOgreIni, posOgreFin);

	//! ESFERA
	Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
	sphere->setMaterialName("Practica1/happyCursed");
	Ogre::SceneNode* happyCursed_ = mSM->getRootSceneNode()->createChildSceneNode("Planeta");
	happyCursed_->attachObject(sphere);
	Vector3 pos = finalPos;
	pos.y = 50;
	happyCursed_->translate(pos);
	happyCursed_->setScale(Vector3(0.3f));
}
#pragma endregion


#pragma region PRACTICA1
void IG2App::scene6_1() {
	//! BOMBA
	Bomba* b = new Bomba(mSM->getRootSceneNode()->createChildSceneNode());
	//a->getMainNode()->setPosition(0, 3700, 0);
	//Hay que hacer otro nodo fuera
	b->getMainNode()->setScale(Vector3(10.0));
	addInputListener(b);
	b->addListener(b);
	entidades.push_back(b);

	//! AVION
	Avion* a = new Avion(mSM->getRootSceneNode()->createChildSceneNode());
	a->getMainNode()->setScale(Vector3(0.3f));
	a->getMainNode()->setPosition(0, 500, -500);
	a->setPlaneAction(Avion::OVERFLY);
	a->setFinalSceneConfig();
	addInputListener(a);
	entidades.push_back(a);

	//! PLANO
	Plano* p = new Plano(mSM->getRootSceneNode()->createChildSceneNode(),
		"mPlane1080x800_2", { 1080 , 800 }, { 100, 80 });
	p->setMaterial("Practica1/Jaja");
	addInputListener(p);
	entidades.push_back(p);

	Vector3 iniPos = { -385, 10, 250 }, finalPos = { 385, 10, -250 };

	//! Plano Amarillo
	Plano* pAmarillo = new Plano(mSM->getRootSceneNode()->createChildSceneNode(),
		"mPlane1080x800_3", { 300 , 300 }, { 100, 80 });
	pAmarillo->setMaterial("Practica1/Yellow");
	pAmarillo->getMainNode()->translate(Vector3(iniPos));
	entidades.push_back(pAmarillo);

	//! Plano Rojo
	Plano* pRojo = new Plano(mSM->getRootSceneNode()->createChildSceneNode(),
		"mPlane1080x800_4", { 300 , 300 }, { 100, 80 });
	pRojo->setMaterial("Practica1/Red");
	pRojo->getMainNode()->translate(finalPos);
	entidades.push_back(pRojo);

	//! Sinbad
	Sinbad* sinBad = new Sinbad(mSM->getRootSceneNode()->createChildSceneNode());
	addInputListener(sinBad);
	sinBad->addListener(sinBad);
	entidades.push_back(sinBad);

	sinBad->arma();
	sinBad->getMainNode()->scale(Vector3(10));
	Vector3 posOgreIni = iniPos, posOgreFin = finalPos;
	posOgreIni.y = posOgreFin.y = 62;
	sinBad->getMainNode()->translate(posOgreIni);
	sinBad->setRoute(posOgreIni, posOgreFin);

	//! ESFERA
	Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
	sphere->setMaterialName("Practica1/happyCursed");
	Ogre::SceneNode* happyCursed_ = mSM->getRootSceneNode()->createChildSceneNode("Planeta");
	happyCursed_->attachObject(sphere);
	Vector3 pos = finalPos;
	pos.y = 50;
	happyCursed_->translate(pos);
	happyCursed_->setScale(Vector3(0.3f));

	//! Niebla
	entidades.push_back(new Fog(mSM->getRootSceneNode()->createChildSceneNode(),
		std::pair<float, float>(800, 800)));
	entidades.back()->getMainNode()->translate(Vector3(200, 200, 200));
}

void IG2App::scene5_1() {
	//! PLANETA
	Ogre::SceneNode* planeta;
	planeta = mSM->getRootSceneNode()->createChildSceneNode("Planeta");
	Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
	sphere->setMaterialName("Practica1/Naboo");
	planeta->attachObject(sphere);
	planeta->setScale(32, 32, 32);

	Sinbad* conBad = new Sinbad(mSM->getRootSceneNode()->createChildSceneNode());

	float size = 60;
	conBad->getMainNode()->setScale(size, size, size);
	conBad->getMainNode()->setPosition(0, 3490, 0);

	addInputListener(conBad);
}

void IG2App::scene4_1() {
	//! PLANETA
	Ogre::SceneNode* planeta;
	planeta = mSM->getRootSceneNode()->createChildSceneNode("Planeta");
	Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
	sphere->setMaterialName("Practica1/Naboo");
	planeta->attachObject(sphere);
	planeta->setScale(32, 32, 32);

	//! AVION
	Avion* a = new Avion(mSM->getRootSceneNode()->createChildSceneNode());
	a->getMainNode()->setPosition(0, 3700, 0);
	a->setPlaneAction(Avion::ORBITATE);
	addInputListener(a);
	entidades.push_back(a);

	//! Enjambre
	Ogre::SceneNode* swarm = mSM->getRootSceneNode()->createChildSceneNode();
	Enjambre* enj = new Enjambre(swarm, a->getMainNode());
	addInputListener(enj);

	entidades.push_back(enj);

	////! DRON
	ficticioDroneNode = mSM->getRootSceneNode()->createChildSceneNode();
	dron = new Dron(ficticioDroneNode, 6, 12);
	addInputListener(dron);
	dron->getMainNode()->scale(0.5, 0.5, 0.5);
	dron->getMainNode()->setPosition(0, 3700, 0);
	entidades.push_back(dron);
	EntityIG::addListener(dron);

	EntityIG::addListener(a);
	//! PLANO
	Plano* p = new Plano(mSM->getRootSceneNode()->createChildSceneNode(), "mPlane1080x800", { 1080 , 800 }, { 100, 80 });
	p->getMainNode()->pitch(Ogre::Degree(90.));
	p->getMainNode()->scale(10, 10, 10);
	p->getMainNode()->setPosition(0, 0, -3600);
}

void IG2App::scene3_1() {
	//Avion
	Avion* a = new Avion(mSM->getRootSceneNode()->createChildSceneNode());
	addInputListener(a);
	entidades.push_back(a);
}

void IG2App::scene2_1() {
	//Planeta
	Ogre::SceneNode* planeta;
	ficticioDroneNode = mSM->getRootSceneNode()->createChildSceneNode();
	planeta = mSM->getRootSceneNode()->createChildSceneNode("Planeta");
	Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
	planeta->attachObject(sphere);
	planeta->setScale(32, 32, 32);
	dron = new Dron(ficticioDroneNode, 6, 12);

	addInputListener(dron);
	dron->getMainNode()->scale(0.5, 0.5, 0.5);
	dron->getMainNode()->setPosition(0, 3600, 0);
	entidades.push_back(dron);
}

void IG2App::scene1_1() {
	//Reloj
	BallClock(1000);
	//Dron

	aspas = new AspasMolino(mSM->getRootSceneNode()->createChildSceneNode(), 12);
	molino = new Molino(mSM->getRootSceneNode()->createChildSceneNode());
	entidades.push_back(new Molino(mSM->getRootSceneNode()->createChildSceneNode()));
	entidades.push_back(new RotorDron(mSM->getRootSceneNode()->createChildSceneNode(), 6));
	entidades.push_back(new BrazoDron(mSM->getRootSceneNode()->createChildSceneNode(), 6));
	Dron* dron = new Dron(mSM->getRootSceneNode()->createChildSceneNode(), 8, 12);
	entidades.push_back(dron);
	float scale = 0.5;
	dron->getMainNode()->translate(700, 500, 400);
	dron->getMainNode()->setScale(scale, scale, scale);
}
#pragma endregion



