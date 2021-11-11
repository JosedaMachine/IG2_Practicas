#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

#include "EntityIG.h"
#include <OgreEntity.h>

#pragma once
using namespace Ogre;

class Plano : public EntityIG
{
public:
	Plano(Ogre::SceneNode* mNode_, std::string const& name, std::pair<int, int > size, std::pair<int, int> cuts);
	virtual ~Plano() {};

	void setMaterial(std::string name) { e->setMaterialName(name); }

private:
	Entity* e;
};

