#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_s) {
	  giraReloj();
  }
  

  //ONgo bongo
  return true;
}

void IG2App::giraReloj()
{
	relojRot += 1;
	Ogre::Vector3 sandokan(0, 0, relojRot);
	reloj->rotate(&sandokan);
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
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

void IG2App::setupScene(void)
{
#pragma region UnHuevoDeMovidas
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

	//------------------------------------------------------------------------
#pragma endregion

  // finally something to render
#pragma region SinBadYSuBañoGuarro
	//Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");

	//mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	//mSinbadNode->attachObject(ent);

	//Ogre::Entity* banio = mSM->createEntity("Columns.mesh");
	//Ogre::Entity* banio1 = mSM->createEntity("RomanBathLower.mesh");
	//Ogre::Entity* banio2 = mSM->createEntity("RomanBathUpper.mesh");

	//banios[0] = mSM->getRootSceneNode()->createChildSceneNode("columnasNodo");
	//banios[0]->attachObject(banio);

	//banios[1] = mSM->getRootSceneNode()->createChildSceneNode("lowerNodo");
	//banios[1]->attachObject(banio1);

	//banios[2] = mSM->getRootSceneNode()->createChildSceneNode("upperNodo");
	//banios[2]->attachObject(banio2);

	////mSinbadNode->setPosition(400, 100, -300);
	//mSinbadNode->setScale(20, 20, 20);
	//mSinbadNode->yaw(Ogre::Degree(-45));
	//mSinbadNode->showBoundingBox(true);
	//mSinbadNode->setVisible(false);

	//-----------------------------------------------------------------------
#pragma endregion
	
#pragma region Reloj
	reloj = mSM->getRootSceneNode()->createChildSceneNode("Reloj");

	float ang = 0;
	float pro = 360.0 / 12;
	float rad = 1000;

	//las esferas del dragón
	for (int i = 0; i < 12; i++) {
		Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");

		mHourNode[i] = mSM->getRootSceneNode()->createChildSceneNode("Hora" + std::to_string(i));
		mHourNode[i]->attachObject(sphere);


		float angle = Ogre::Math::DegreesToRadians(ang);
		//Pos original en la x + seno del angulo por el radio
		mHourNode[i]->setPosition(Ogre::Math::Sin(angle) * rad, Ogre::Math::Cos(angle) * rad, 0);

		ang = ang + pro;

		//Hacer más pequeñas las pares

		//No lo hago así porque Antonio dice que es de feos
		//if(i%2 == 0) mHourNode[i]->setScale(0.5, 0.5, 0.5);
	}

	//Hacerlas más pequeñas
	for (int i = 0; i < 12; i = i + 2) {
		mSM->getSceneNode("Hora" + std::to_string(i))->setScale(0.4, 0.4, 0.4);
	}

	//Como decia Melendi, las manecillas del reloj
	for (int i = 0; i < 3; i++) {
		Ogre::Entity* maneciglia = mSM->createEntity("cube.mesh");

		maneciglias[i] = mSM->getRootSceneNode()->createChildSceneNode("Maneciglia" + std::to_string(i));
		maneciglias[i]->attachObject(maneciglia);

	}

	maneciglias[0]->setScale(0.3, 8, 0.3);
	maneciglias[0]->setPosition(0, 400, 0);

	maneciglias[1]->setScale(8, 0.6, 0.6);
	maneciglias[1]->setPosition(350, 0, 0);

	maneciglias[2]->setScale(0.8, -4, 0.6);
	maneciglias[2]->setPosition(0, -200, 0);
#pragma endregion

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}