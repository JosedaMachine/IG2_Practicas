#include "EntityIG.h"
#include <OgreTimer.h>

#pragma once
class Bomba : public EntityIG {
	const float stopTime = 5000;

public:
	Bomba(Ogre::SceneNode* _node);
	virtual	~Bomba();

private:
	Ogre::AnimationState* animationState;
	Ogre::SceneNode* animationNode;

	Ogre::Timer timer;

	bool stopped = false;

	// Heredado vía EntityIG
	virtual void frameRendered(Ogre::FrameEvent const& evt) override;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
};

