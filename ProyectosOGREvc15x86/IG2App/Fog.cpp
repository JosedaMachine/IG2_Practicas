#include "Fog.h"

Fog::Fog(Ogre::SceneNode* mNode_, std::pair<int, int> size) : EntityIG(mNode_)
{
	//numberOfFogs++;

	boards = mSM->createBillboardSet("Efectivamente Niebla", nBoards);
	boards->setDefaultDimensions(size.first, size.second);
	boards->setMaterialName("Practica1/Smoke");

	mNode->attachObject(boards);

	boards->createBillboard(Ogre::Vector3(0, 0, 0));
}
