#pragma once

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>a

#include "Aspas.h"

#include "EntityIG.h"

class AspasMolino : public EntityIG {
public:
	AspasMolino(Ogre::SceneManager* mSM, bool hasOrnament, const int& numAspas_ = 12, Ogre::SceneNode* parentNode = nullptr);

	~AspasMolino();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	void FixOrnamentRot(const float& rotation);
	Ogre::SceneNode* getMainNode() const { return mNode; }
	Ogre::SceneNode* getAspasNode() const { return aspasNode; }

	void setClockWise(const bool& state);
private:
	Ogre::SceneManager* mSM = nullptr;
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* cilindroCentralNode = nullptr;
	Ogre::SceneNode* aspasNode = nullptr;

	int numAspas;
	float degrees = 3.;
	bool clockWise = true;
	std::vector<Aspa*> arrayAspas;
};


using Helices = AspasMolino;

