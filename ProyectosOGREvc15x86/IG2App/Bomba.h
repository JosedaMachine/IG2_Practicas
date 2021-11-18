#include "EntityIG.h"
#include <OgreParticleSystem.h>

#pragma once
class Bomba : public EntityIG {

public:
	Bomba(Ogre::SceneNode* _node);
	virtual	~Bomba();

private:
	Ogre::AnimationState* animationState;
	Ogre::SceneNode* animationNode;

	Ogre::ParticleSystem* ex = nullptr;

	bool stopped = false;

	// Heredado vía EntityIG
	virtual void frameRendered(Ogre::FrameEvent const& evt) override;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	virtual void receiveEvent(Message mes, EntityIG* entidad = nullptr) override;
};

