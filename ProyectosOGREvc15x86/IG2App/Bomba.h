#include "EntityIG.h"
#pragma once
class Bomba : public EntityIG {
public:
	Bomba(Ogre::SceneNode* _node);
	virtual	~Bomba();

private:
	// Heredado vía EntityIG
	virtual void frameRendered(Ogre::FrameEvent const& evt) override;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
};

