#pragma once
#include "EntityIG.h"
class HappyCursedSatanicFace : public EntityIG
{

private:
	Ogre::Entity* s;
	Ogre::Vector3 p;

public:
	HappyCursedSatanicFace(Ogre::SceneNode* mNode_, Ogre::Vector3 pos);



protected:
	virtual void receiveEvent(Message mes, EntityIG* entidad);

};

