#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreBillboardSet.h>
#include <OgreBillboard.h>

//Entitdades
#include "Aspas.h"
#include "AspasMolino.h"
#include "Molino.h"
#include "Dron.h"
#include "Avion.h"
#include "Plano.h"
#include "Sinbad.h"
#include "Enjambre.h"
#include "Bomba.h"
#include "Fog.h"

#include "EntityIG.h"
class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();


  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener

  //Metodos de pulsar
  void BallClock(float rad);
  
#pragma region P2
  void scene1_2();

#pragma endregion


  #pragma region P1
  void scene6_1();

  void scene5_1();

  void scene4_1();

  void scene1_1();

  void scene2_1();

  void scene3_1();
#pragma endregion
  
  void setCamNLight();
      
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mSinbadNode = nullptr;

  //Ba�o dios que pereza no lo quiero hacer
  Ogre::SceneNode* banios[3];

  //arrayDelReloj
  Ogre::SceneNode* mHourNode[12];
  Ogre::SceneNode* manecillas[3];
  Ogre::SceneNode* reloj;
  Ogre::SceneNode* centroEsferas;

  AspasMolino* aspas = nullptr;
  Molino* molino = nullptr;
  Dron* dron = nullptr;
 
  OgreBites::CameraMan* mCamMgr = nullptr;

  std::vector<EntityIG*> entidades;

  Ogre::SceneNode* ficticioDroneNode = nullptr;

  //Plano
  Ogre::SceneNode* plano = nullptr;

};


#endif
