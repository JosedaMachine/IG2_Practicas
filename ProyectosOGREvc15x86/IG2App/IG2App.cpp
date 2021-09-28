#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE){
    getRoot()->queueEndRendering();
  }
  //ONgo bongo Buga Buga Bo 
  return true;
}

void IG2App::BallClock(float rad) {
	reloj = mSM->getRootSceneNode()->createChildSceneNode("Reloj");

	centroEsferas = reloj->createChildSceneNode("centroEsferas");
	float ang = 0;
	float pro = 360.0 / 12;

	//las esferas del dragón
	for (int i = 0; i < 12; i++) {
		Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");

		mHourNode[i] = centroEsferas->createChildSceneNode("Hora" + std::to_string(i));
		mHourNode[i]->attachObject(sphere);

		float angle = Ogre::Math::DegreesToRadians(ang);
		//Pos original en la x + seno del angulo por el radio
		mHourNode[i]->setPosition(Ogre::Math::Sin(angle) * rad, Ogre::Math::Cos(angle) * rad, 0);
		ang += pro;

		//Hacer más pequeñas las pares
		//No lo hago así porque Antonio dice que es de feos
		//if(i%2 == 0) mHourNode[i]->setScale(0.5, 0.5, 0.5);
	}

	//Hacerlas más pequeñas
	for (int i = 0; i < 12; i = i + 2)
		mSM->getSceneNode("Hora" + std::to_string(i))->setScale(0.4, 0.4, 0.4);

	//Como decia Melendi, las manecillas del reloj
	for (int i = 0; i < 3; i++) {
		Ogre::Entity* manecilla = mSM->createEntity("cube.mesh");

		manecillas[i] = reloj->createChildSceneNode("Manecilla" + std::to_string(i));
		manecillas[i]->attachObject(manecilla);
	}

	//Configurar para que de igual el tamaño, se ponga bien
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
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);
}


void IG2App::shutdown() {
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
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

	setCamNLight();
  // finally something to render
	//BallClock(1000);

	std::string joseda = "Joseda";
	
	rot = new RotorDron(mSM);

	addInputListener(rot);

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------
}
