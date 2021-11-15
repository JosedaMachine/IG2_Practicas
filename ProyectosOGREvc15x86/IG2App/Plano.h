#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include "EntityIG.h"
#include <OgreEntity.h>
#include <OgreTimer.h>

#pragma once
using namespace Ogre;

class Plano : public EntityIG
{
	const float stopTime = 5000;
public:
	Plano(Ogre::SceneNode* mNode_, std::string const& name, std::pair<int, int > size, std::pair<int, int> cuts);
	virtual ~Plano() {};

	void setMaterial(std::string name) { e->setMaterialName(name); }
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
private:
	Entity* e;

	bool dry;

	Ogre::Timer timer;
};

