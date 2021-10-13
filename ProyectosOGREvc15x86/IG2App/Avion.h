#pragma once
#include "EntityIG.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include "AspasMolino.h"

class Avion: public EntityIG
{
public:
	Avion(Ogre::SceneNode * mNode_);

	void crearLuz();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:

	Ogre::SceneNode* cuerpoNode = nullptr;
	Ogre::SceneNode* alaINode = nullptr;
	Ogre::SceneNode* alaDNode = nullptr;
	Ogre::SceneNode* fernteNode = nullptr;
	Ogre::SceneNode* pilotoNode = nullptr;
	std::vector<AspasMolino*> heliceNodes;

	Ogre::SceneNode* light = nullptr;

	void alaIzquierda();
	void alaDerecha();
	void frente();
	void pilotoNinja();
	void helices();
};

