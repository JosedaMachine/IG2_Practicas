#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "IG2ApplicationContext.h"
#include <OgreTrays.h>
#include <OgreCameraMan.h>

class Aspa
{
public:
	Aspa(Ogre::SceneManager* mSM, const std::string& name);
	~Aspa();

	Ogre::SceneNode* getMainNode() const { return mNode; }
	Ogre::SceneNode* getTabNode() const { return tableroNode; }
	Ogre::SceneNode* getOrnamentNode() const { return adornoNode; }

private:
	Ogre::SceneManager* mSM = nullptr;

	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* tableroNode = nullptr;
	Ogre::SceneNode* adornoNode = nullptr;
};

