#include "EntityIG.h"
#include "Dron.h"
#pragma once
class Enjambre : public EntityIG {
public:
	Enjambre(Ogre::SceneNode* _node, Ogre::SceneNode* avionNode);

	~Enjambre();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	virtual void frameRendered(Ogre::FrameEvent const& evt);

private:

	Dron* controlDron;
	Ogre::SceneNode* avionNode_;
	std::vector<Dron*> drons;
};

