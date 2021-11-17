#pragma once
#include "EntityIG.h"
#include <OgreBillboard.h>
#include <OgreBillboardSet.h>


class Fog :public EntityIG
{
	//static int numberOfFogs;

	const int nBoards = 10000;
private:
	Ogre::BillboardSet* boards;

public:
	Fog(Ogre::SceneNode* mNode_,
		std::pair<int, int > size);

	virtual ~Fog() {};
};

