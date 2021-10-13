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
	
	static std::vector<EntityIG*> appListeners; //Para mandar eventos. Van por otro lado

	static void addListener(EntityIG* entidad) {
		appListeners.push_back(entidad);
	};

	Ogre::SceneNode* getMainNode() const { return mNode; }

protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) { return false; };

};

