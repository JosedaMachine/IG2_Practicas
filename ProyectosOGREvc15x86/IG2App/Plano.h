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
	Plano(Ogre::SceneNode* mNode_, std::string const& name, std::pair<int, int > size, std::pair<int, int> cuts, Vector3 normal = Vector3::UNIT_Y);
	virtual ~Plano() {};

	void setMaterial(std::string name) { e->setMaterialName(name); }
	void setEspejo(Camera* cam);
	void setReflejo(Camera* cam);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	virtual void frameRendered(Ogre::FrameEvent const& evt);
private:
	Entity* e;
	Vector3 normal;
	bool dry;

	Ogre::Timer timer;
};

