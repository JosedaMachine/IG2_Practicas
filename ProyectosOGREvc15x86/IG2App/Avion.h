#pragma once
#include "EntityIG.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include "AspasMolino.h"

class Avion: public EntityIG
{
public:
	Avion(Ogre::SceneManager* mSM_, Ogre::SceneNode* father = nullptr);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:

	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* cuerpoNode = nullptr;
	Ogre::SceneNode* alaINode = nullptr;
	Ogre::SceneNode* alaDNode = nullptr;
	Ogre::SceneNode* fernteNode = nullptr;
	Ogre::SceneNode* pilotoNode = nullptr;
	std::vector<AspasMolino*> heliceNodes;

	Ogre::SceneManager* mSM = nullptr;


	void alaIzquierda();
	void alaDerecha();
	void frente();
	void pilotoNinja();
	void helices();
};

