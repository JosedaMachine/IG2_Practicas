#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "IG2ApplicationContext.h"
#include <OgreTrays.h>
#include <OgreEntity.h>
#include <OgreCameraMan.h>

class Aspa
{
public:
	Aspa(Ogre::SceneManager* mSM, Ogre::SceneNode* nodeParent = nullptr, bool showOrnament = true);
	~Aspa();

	Ogre::SceneNode* getMainNode() const { return mNode; }
	Ogre::SceneNode* getTabNode() const { return tableroNode; }
	Ogre::SceneNode* getOrnamentNode() const { return adornoNode; }
	bool hasOrnament() const { return showOrnament_; }

private:
	//Tener o no adorno en las aspas
	bool showOrnament_;

	Ogre::SceneManager* mSM = nullptr;
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* tableroNode = nullptr;
	Ogre::SceneNode* adornoNode = nullptr;

};


