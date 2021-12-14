#include "HappyCursedSatanicFace.h"
#include <OgreEntity.h>

HappyCursedSatanicFace::HappyCursedSatanicFace(Ogre::SceneNode* mNode_, Ogre::Vector3 pos) : EntityIG(mNode_)
{
	s = mSM->createEntity("sphere.mesh");

	p = pos;

	mNode->attachObject(s);

	mNode->translate(p);
	mNode->setScale(Ogre::Vector3(0.3f));
}

void HappyCursedSatanicFace::receiveEvent(Message mes, EntityIG* entidad)
{
	switch (mes.m)
	{
	case HappyInvBeing:
		
		s->setMaterialName("Practica1/happyCursed_Inv");

		break;
	case HappyInvFinal:

		s->setMaterialName("Practica1/happyCursed");

		break;
	default:
		break;
	}
}
