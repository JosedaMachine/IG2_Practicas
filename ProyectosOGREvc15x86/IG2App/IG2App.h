#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "Aspas.h"


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

  OgreBites::CameraMan* mCamMgr = nullptr;
 
};


#endif
