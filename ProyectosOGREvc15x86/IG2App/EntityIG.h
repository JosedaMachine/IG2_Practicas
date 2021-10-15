#pragma once
#include <OgreInput.h>
#include "IG2ApplicationContext.h"
#include <SDL_keycode.h>

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

class EntityIG : public OgreBites::InputListener {

public:
	EntityIG(Ogre::SceneNode* node);
	~EntityIG();
	
	Ogre::SceneNode* getMainNode() const { return mNode; }
	
	virtual void frameRendered(Ogre::FrameEvent const& evt) {};
	
	static std::vector<EntityIG*> appListeners; //Para mandar eventos. Van por otro lado

	static void addListener(EntityIG* entidad) {
		appListeners.push_back(entidad);
	};
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) { return false; };

};

