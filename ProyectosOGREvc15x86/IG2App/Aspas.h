#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "IG2ApplicationContext.h"
#include <OgreTrays.h>
#include <OgreCameraMan.h>

class Aspa
{
public:
	Aspa(Ogre::SceneManager* mSM, const std::string& name, bool adorn = true);
	~Aspa();

	Ogre::SceneNode* getNode() const {
		return mNode;
	}

	void setFather(Ogre::SceneNode* f);

private:
	Ogre::SceneManager* mSM = nullptr;

	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* tableroNode = nullptr;
	Ogre::SceneNode* adornoNode = nullptr;
};

